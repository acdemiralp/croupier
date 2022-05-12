#ifndef CROUPIER_EVALUATOR_EVALUATOR_HPP
#define CROUPIER_EVALUATOR_EVALUATOR_HPP

#include <cstddef>
#include <cstdint>
#include <limits>
#include <vector>

#include <croupier/card/card_set_ops.hpp>
#include <croupier/evaluator/equivalences.hpp>
#include <croupier/evaluator/hand_evaluation.hpp>
#include <croupier/game/table.hpp>
#include <croupier/ruleset/ruleset.hpp>

namespace cro
{
class evaluator
{
public:
  evaluator           (ruleset* ruleset, table* table)
  : ruleset_     (ruleset)
  , table_       (table)
  , equivalences_(make_equivalences())
  {
    
  }
  evaluator           (const evaluator&  that) = default;
  evaluator           (      evaluator&& temp) = default;
 ~evaluator           ()                       = default;
  evaluator& operator=(const evaluator&  that) = default;
  evaluator& operator=(      evaluator&& temp) = default;

  [[nodiscard]]
  std::vector<hand_evaluation>                evaluate               (const bool open_only = false) const
  {
    auto evaluations = std::vector<hand_evaluation>(table_->players_.size());
    table_->active_players_.iterate([&] (const std::size_t index)
    {
      const auto& player = table_->players_[index];
      evaluations[index] = evaluate(open_only ? player.open_cards : player.open_cards | player.closed_cards);
    });
    return evaluations;
  }
  [[nodiscard]]
  hand_evaluation                             evaluate               (const card_set& cards) const
  {
    const auto combinations = make_combinations(cards, table_->community_cards_);
    auto       evaluation   = hand_evaluation {hand_type(), std::numeric_limits<std::uint16_t>::max()};
    for (auto& combination : combinations)
      evaluation = std::min(evaluation, equivalences_.at(ruleset_->ranking_type).at(combination.count()).at(compute_equivalence_key(combination)));
    return evaluation;
  }

  [[nodiscard]]
  std::vector<hand_evaluation>                evaluate_low           (const bool open_only = false) const
  {
    auto evaluations = std::vector<hand_evaluation>(table_->players_.size());
    table_->active_players_.iterate([&] (const std::size_t index)
    {
      const auto& player = table_->players_[index];
      evaluations[index] = evaluate_low(open_only ? player.open_cards : player.open_cards | player.closed_cards);
    });
    return evaluations;
  }
  [[nodiscard]]
  hand_evaluation                             evaluate_low           (const card_set& cards) const
  {
    const auto combinations = make_combinations(cards, table_->community_cards_);
    auto       evaluation   = hand_evaluation {hand_type(), 0};
    for (auto& combination : combinations)
      evaluation = std::max(evaluation, equivalences_.at(ruleset_->ranking_type).at(combination.count()).at(compute_equivalence_key(combination)));
    return evaluation;
  }

  [[nodiscard]]
  std::vector<std::array<hand_evaluation, 2>> evaluate_high_low      (const bool open_only = false) const
  {
    auto evaluations = std::vector<std::array<hand_evaluation, 2>>(table_->players_.size());
    table_->active_players_.iterate([&] (const std::size_t index)
    {
      const auto& player = table_->players_[index];
      evaluations[index] = evaluate_high_low(open_only ? player.open_cards : player.open_cards | player.closed_cards);
    });
    return evaluations;
  }
  [[nodiscard]]
  std::array<hand_evaluation, 2>              evaluate_high_low      (const card_set& cards) const
  {
    const auto combinations    = make_combinations(cards, table_->community_cards_);
    auto       high_evaluation = hand_evaluation {hand_type(), std::numeric_limits<std::uint16_t>::max()};
    auto       low_evaluation  = hand_evaluation {hand_type(), 0};
    for (auto& combination : combinations)
    {
      auto evaluation = equivalences_.at(ruleset_->ranking_type).at(combination.count()).at(compute_equivalence_key(combination));
      high_evaluation = std::min(high_evaluation, evaluation);
      low_evaluation  = std::max(low_evaluation , evaluation);
    }
    return {high_evaluation, low_evaluation};
  }

protected:
  [[nodiscard]]
  std::vector<card_set>                       make_combinations      (const card_set& cards, const std::optional<card_set> community_cards) const
  {
    if (ruleset_->evaluated_community_cards)
      return community_cards->combinations(*ruleset_->evaluated_community_cards) | cards.combinations(ruleset_->evaluated_cards - *ruleset_->evaluated_community_cards);
    return (community_cards ? cards | *community_cards : cards).combinations(ruleset_->evaluated_cards);
  }
  [[nodiscard]]
  static std::int32_t                         compute_equivalence_key(const card_set& cards)
  {
    auto key = 1;

    const auto split = cards.cards();
    for (auto& card : split)
      key *= rank_to_prime(card.rank());    // Multiply the prime of each card rank in card_set.

    for (auto& suit_mask : suit_masks)
      if ((cards & suit_mask).count() == 5) // If the card_set is a flush, negate.
        key *= -1;

    return key;
  }

  ruleset*     ruleset_     ;
  table*       table_       ;
  equivalences equivalences_;
};
}

#endif