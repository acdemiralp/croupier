#ifndef CROUPIER_EVALUATOR_EVALUATOR_HPP
#define CROUPIER_EVALUATOR_EVALUATOR_HPP

#include <cstddef>
#include <cstdint>
#include <limits>
#include <vector>

#include <croupier/card/card_set_ops.hpp>
#include <croupier/evaluator/equivalence_class.hpp>
#include <croupier/evaluator/hand_evaluation.hpp>
#include <croupier/ruleset/ruleset.hpp>
#include <croupier/table.hpp>

namespace cro
{
class evaluator
{
public:
  evaluator           (ruleset* ruleset, table* table)
  : ruleset_              (ruleset)
  , table_                (table  )
  , rank_masks_           (make_rank_masks    ())
  , suit_masks_           (make_suit_masks    ())
  , straight_masks_       (make_straight_masks())
  , equivalence_class_map_(make_equivalence_class_map(ruleset_->ranking_type))
  {
    
  }
  evaluator           (const evaluator&  that) = default;
  evaluator           (      evaluator&& temp) = default;
 ~evaluator           ()                       = default;
  evaluator& operator=(const evaluator&  that) = default;
  evaluator& operator=(      evaluator&& temp) = default;

  std::vector<hand_evaluation> evaluate(bool open_cards_only = false) const
  {
    auto scores = std::vector<hand_evaluation>(table_->players_.size());
    table_->active_players_.iterate([&] (const std::size_t index)
    {
      const auto& open_cards      = table_->players_[index].open_cards;
      const auto& closed_cards    = table_->players_[index].closed_cards;
      const auto& community_cards = table_->community_cards_;
      scores[index] = evaluate(open_cards_only ? open_cards : open_cards | closed_cards, community_cards);
    });
    return scores;
  }

  hand_evaluation              evaluate(const card_set& cards, std::optional<card_set> community_cards = std::nullopt) const
  {
    auto combinations = make_combinations(cards, community_cards);
    auto evaluation   = hand_evaluation {hand_type::high_card, std::numeric_limits<std::uint16_t>::max()}; // TODO: Distinguish traditional/lowball/highlow. TODO: Equivalency tables for 2/3/4 (open) cards?
    for (auto& combination : combinations)
      evaluation = std::min(evaluation, equivalence_class_map_.at(compute_equivalence_key(combination)));
    return evaluation;
  }

protected:
  std::vector<card_set> make_combinations      (const card_set& cards, std::optional<card_set> community_cards) const
  {
    if (ruleset_->evaluated_community_cards)
      return community_cards->combinations(*ruleset_->evaluated_community_cards) | cards.combinations(ruleset_->evaluated_cards - *ruleset_->evaluated_community_cards);
    return (community_cards ? cards | *community_cards : cards).combinations(ruleset_->evaluated_cards);
  }
  std::int32_t          compute_equivalence_key(const card_set& cards) const
  {
    auto key = std::int32_t(1);

    auto split = cards.cards();
    for (auto& card : split)
      key *= rank_to_prime(card.rank());    // Multiply the prime of each card rank in card_set.

    for (auto& suit_mask : suit_masks_)
      if ((cards & suit_mask).count() == 5) // If the card_set is a flush, negate.
        key *= -1;

    return key;
  }

  ruleset*                                          ruleset_              ;
  table*                                            table_                ;
  std::vector<card_set>                             rank_masks_           ;
  std::vector<card_set>                             suit_masks_           ;
  std::vector<std::bitset<13>>                      straight_masks_       ;
  std::unordered_map<std::int32_t, hand_evaluation> equivalence_class_map_;
};
}

#endif