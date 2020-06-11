#ifndef CROUPIER_GAME_DEALER_HPP
#define CROUPIER_GAME_DEALER_HPP

#include <limits>
#include <stdexcept>
#include <vector>

#include <croupier/evaluator/evaluator.hpp>
#include <croupier/ruleset/ruleset.hpp>
#include <croupier/game/betting_state.hpp>
#include <croupier/game/event.hpp>
#include <croupier/game/table.hpp>

namespace cro
{
class dealer : public evaluator
{
public:
  dealer           (ruleset* ruleset, table* table, std::vector<std::vector<event>>* history) : evaluator(ruleset, table), ruleset_(ruleset), table_(table), history_(history)
  {

  }
  dealer           (const dealer&  that) = default;
  dealer           (      dealer&& temp) = default;
 ~dealer           ()                    = default;
  dealer& operator=(const dealer&  that) = default;
  dealer& operator=(      dealer&& temp) = default;

  void play                                   () const
  {
    initialize  ();
    apply_stages();
    finalize    ();
  }

protected:
  void initialize                             () const
  {
    // Set players with sufficient funds to active.
    const auto minimum_chips = (ruleset_->ante ? ruleset_->ante.value() : 0ull) + (ruleset_->blinds ? ruleset_->blinds->big_blind : 0ull);
    for (std::size_t i = 0; i < table_->players_.size(); ++i)
      if (table_->players_[i].chips >= minimum_chips)
        table_->active_players_[i] = true;

    // If a player has the button, pass it to the next active player, else give it to the first active player.
    if (table_->button_player_.count())
    {
      const auto current = table_->button_player_ .find_first();
      const auto next    = table_->active_players_.find_next_circular(current);
      table_->button_player_[current] = false;
      table_->button_player_[next   ] = true;
    }
    else
      table_->button_player_[table_->active_players_.find_first()] = true;

    // If fixed limit applies, set current limit to small bet.
    if (ruleset_->limit_type == limit_type::fixed_limit)
      table_->fixed_limit_ = ruleset_->fixed_limits->small_bet;
  }
  void apply_stages                           () const
  {
    for (auto& stage : ruleset_->stages)
    {
      if (stage == stage::ante                           ) apply_ante                             ();
      if (stage == stage::betting_from_left_of_the_button) apply_betting_from_left_of_the_button  ();
      if (stage == stage::betting_from_best_open         ) apply_betting_from_best_open           ();
      if (stage == stage::blind                          ) apply_blind                            ();
      if (stage == stage::bring_in                       ) apply_bring_in                         ();
      if (stage == stage::burn_card                      ) apply_burn_card                        ();
      if (stage == stage::deal_closed_card               ) apply_deal_closed_card                 ();
      if (stage == stage::deal_community_card            ) apply_deal_community_card              ();
      if (stage == stage::deal_open_card                 ) apply_deal_open_card                   ();
      if (stage == stage::deal_replacement_cards         ) apply_deal_replacement_cards           ();
      if (stage == stage::increase_limit                 ) apply_increase_limit                   ();
      if (stage == stage::showdown                       ) apply_showdown                         ();
    }
  }
  void apply_ante                             () const
  {
    const auto amount = ruleset_->ante.value_or(0);
    table_->active_players_.iterate([&] (const std::size_t index)
    {
      table_->players_[index].chips          -= amount;
      table_->pots_[table_->active_players_] += amount;
    });
    history_->back().push_back(event {event_type::ante, table_->active_players_, std::nullopt, amount});
  }
  void apply_betting                          (const std::size_t start) const
  {
    auto state = betting_state(table_->active_players_);
    auto index = start;
    while (table_->active_players_ != state.complying_players)
    {
      auto& player = table_->players_[index];
      auto  action = player.decision_function(&player, table_, state);

      if      (action.type == action_type::check)
      {
        if (state.bet_to_match)
          throw std::logic_error("Can't check when there is a bet to match. Call, raise or fold instead.");

        state.complying_players[index] = true;

        history_->back().push_back(event {event_type::check, player_set(player)});
      }
      else if (action.type == action_type::bet  )
      {
        if (state.bet_to_match)
          throw std::logic_error("Can't bet when there is a bet to match. Raise instead.");
        if (*action.value > player.chips)
          throw std::logic_error("Can't bet more than what you have.");

        // Enforce fixed/pot limits? We currently only inform the user. A bot would be specific to a limit anyway.

        player.chips                   -= *action.value;
        state.bet_amounts      [index] += *action.value;
        state.complying_players.reset();
        state.complying_players[index]  = true;

        history_->back().push_back(event {event_type::bet  , player_set(player), std::nullopt, action.value});
      }
      else if (action.type == action_type::call )
      {
        if (!state.bet_to_match)
          throw std::logic_error("Can't call when there is no bet to match. Check instead.");

        // Call all-in if the chips are below the bet to match.
        // This also handles cases where a user is out of chips but others continue to sub-pots, in which to user simply calls.
        const auto amount = std::min(player.chips, state.bet_to_match.value() - state.bet_amounts[index]);

        player.chips                   -= amount;
        state.bet_amounts      [index] += amount;
        state.complying_players[index]  = true;

        history_->back().push_back(event {event_type::call , player_set(player), std::nullopt, action.value});
      }
      else if (action.type == action_type::raise)
      {
        if (!state.bet_to_match)
          throw std::logic_error("Can't raise when there is no bet to match. Bet instead.");
        if (*action.value > player.chips)
          throw std::logic_error("Can't raise more than what you have.");
        if (*action.value + state.bet_amounts[index] <= state.bet_to_match)
          throw std::logic_error("Can't raise less than or equal to the bet to match.");
        if (ruleset_->raise_cap.has_value() && ++state.raises > ruleset_->raise_cap.value())
          throw std::logic_error("Can't raise further. Raise cap has been reached.");

        // Enforce fixed/pot limits? We currently only inform the user. A bot would be specific to a limit anyway.

        player.chips                   -= *action.value;
        state.bet_amounts      [index] += *action.value;
        state.complying_players.reset();
        state.complying_players[index] = true;

        history_->back().push_back(event {event_type::raise, player_set(player), std::nullopt, action.value});
      }
      else if (action.type == action_type::fold )
      {
        table_->active_players_[index] = false;

        history_->back().push_back(event {event_type::fold , player_set(player)});
      }

      index = table_->active_players_.find_next(index);
    }

    while (!std::all_of(state.bet_amounts.begin(), state.bet_amounts.end(), [ ] (const std::uint64_t value) { return value == 0; }))
    {
      auto minimum_non_zero_bet = std::numeric_limits<std::uint64_t>::max();
      for (auto i = 0; i < state.bet_amounts.size(); ++i)
      {
        if (state.bet_amounts[i] != 0 && minimum_non_zero_bet > state.bet_amounts[i])
          minimum_non_zero_bet = state.bet_amounts[i];
      }

      auto players = player_set(table_->active_players_.size());
      auto total   = std::uint64_t(0);
      for (auto i = 0; i < state.bet_amounts.size(); ++i)
      {
        if (state.bet_amounts[i] >= minimum_non_zero_bet)
        {
          state.bet_amounts[i] -= minimum_non_zero_bet;
          total                += minimum_non_zero_bet;
          players[i]            = true;
        }
      }
      table_->pots_[players] += total;
    }
  }
  void apply_betting_from_left_of_the_button  () const
  {
    const auto small_blind_index = table_->active_players_.find_next_circular(table_->button_player_.find_first());
    history_->back().push_back(event {event_type::betting_from_left_of_the_button, player_set(table_->players_[small_blind_index])});
    apply_betting(small_blind_index);
  }
  void apply_betting_from_best_open           () const
  {
    const auto evaluations  = evaluate(true);
    const auto player_index = std::distance(evaluations.begin(), std::min_element(evaluations.begin(), evaluations.end()));
    history_->back().push_back(event {event_type::betting_from_best_open, player_set(table_->players_[player_index])});
    apply_betting(player_index);
  }
  void apply_blind                            () const
  {
    const auto small_blind_index  = table_->active_players_.find_next_circular(table_->button_player_.find_first());
    const auto small_blind_amount = ruleset_->blinds ? ruleset_->blinds->small_blind : 0;
    table_->players_[small_blind_index].chips -= small_blind_amount;
    table_->pots_[table_->active_players_]    += small_blind_amount;
    history_->back().push_back(event {event_type::blind, player_set(table_->players_[small_blind_index]), std::nullopt, small_blind_amount});

    const auto big_blind_index    = table_->active_players_.find_next_circular(small_blind_index);
    const auto big_blind_amount   = ruleset_->blinds ? ruleset_->blinds->big_blind   : 0;
    table_->players_[big_blind_index  ].chips -= big_blind_amount;
    table_->pots_[table_->active_players_]    += big_blind_amount;
    history_->back().push_back(event {event_type::blind, player_set(table_->players_[big_blind_index]), std::nullopt, big_blind_amount});

    apply_betting(table_->active_players_.find_next_circular(big_blind_index));
  }
  void apply_bring_in                         () const
  {
    const auto evaluations     = evaluate_low(true);
    const auto player_index    = std::distance(evaluations.begin(), std::max_element(evaluations.begin(), evaluations.end()));
    const auto bring_in_amount = ruleset_->bring_in ? *ruleset_->bring_in : 0;
    table_->players_[player_index].chips   -= bring_in_amount;
    table_->pots_[table_->active_players_] += bring_in_amount;
    history_->back().push_back(event {event_type::bring_in, player_set(table_->players_[player_index]), std::nullopt, bring_in_amount});

    apply_betting(table_->active_players_.find_next_circular(player_index));
  }
  void apply_burn_card                        () const
  {
    const auto card = table_->deck_.draw();
    history_->back().push_back(event {event_type::burn_card, std::nullopt, card_set(card)});
  }
  void apply_deal_closed_card                 () const
  {
    const auto small_blind_index = table_->active_players_.find_next_circular(table_->button_player_.find_first());
    table_->active_players_.iterate_circular(small_blind_index, [&] (const std::size_t index)
    {
      auto& player = table_->players_[index];
      auto  card   = table_->deck_.draw();
      player.closed_cards.insert(card);
      history_->back().push_back(event {event_type::deal_closed_card, player_set(player), card_set(card)});
    });
  }
  void apply_deal_community_card              () const
  {
    const auto card = table_->deck_.draw();
    table_->community_cards_.insert(card);
    history_->back().push_back(event {event_type::deal_community_card, std::nullopt, card_set(card)});
  }
  void apply_deal_open_card                   () const
  {
    const auto small_blind_index = table_->active_players_.find_next_circular(table_->button_player_.find_first());
    table_->active_players_.iterate_circular(small_blind_index, [&] (const std::size_t index)
    {
      auto& player = table_->players_[index];
      auto  card   = table_->deck_.draw();
      player.open_cards.insert(card);
      history_->back().push_back(event {event_type::deal_open_card, player_set(player), card_set(card)});
    });
  }
  void apply_deal_replacement_cards           () const
  {
    const auto small_blind_index = table_->active_players_.find_next_circular(table_->button_player_.find_first());
    table_->active_players_.iterate_circular(small_blind_index, [&] (const std::size_t index)
    {
      auto& player        = table_->players_[index];
      auto  removed_cards = player.card_replacement_function(&player, table_, ruleset_->maximum_replacement_cards);
      // Enforce maximum_replacement_cards limit? We currently only inform the user.

      auto removed_closed_cards = removed_cards & player.closed_cards;
      auto added_closed_cards   = card_set();
      for (auto i = 0; i < removed_closed_cards.count(); ++i)
        added_closed_cards.insert(table_->deck_.draw());
      player.closed_cards.erase (removed_closed_cards);
      player.closed_cards.insert(added_closed_cards);

      auto removed_open_cards = removed_cards & player.open_cards;
      auto added_open_cards   = card_set();
      for (auto i = 0; i < removed_open_cards.count(); ++i)
        added_open_cards.insert(table_->deck_.draw());
      player.open_cards.erase (removed_open_cards);
      player.open_cards.insert(added_open_cards);

      history_->back().push_back(event {event_type::deal_replacement_cards, player_set(player), added_closed_cards | added_open_cards });
    });
  }
  void apply_increase_limit                   () const
  {
    table_->fixed_limit_ = ruleset_->fixed_limits->big_bet;
    history_->back().push_back(event {event_type::increase_limit, std::nullopt, std::nullopt, ruleset_->fixed_limits->big_bet});
  }
  void apply_showdown                         () const
  {
    // TODO: Compute best/worst hands according to the ruleset and distribute pots.
  }
  void finalize                               () const
  {
    for (auto& player : table_->players_)
    {
      player.open_cards  .reset();
      player.closed_cards.reset();
    }
    table_->active_players_ .reset  ();
    table_->deck_           .reset  ();
    table_->deck_           .shuffle();
    table_->pots_           .clear  ();
    table_->community_cards_.reset  ();
    table_->fixed_limit_    .reset  ();
  }

  ruleset*                         ruleset_;
  table*                           table_  ;
  std::vector<std::vector<event>>* history_;
};
}

#endif