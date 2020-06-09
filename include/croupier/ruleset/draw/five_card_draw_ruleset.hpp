#ifndef CROUPIER_RULESET_DRAW_FIVE_CARD_DRAW_RULESET_HPP
#define CROUPIER_RULESET_DRAW_FIVE_CARD_DRAW_RULESET_HPP

#include <croupier/ruleset/ruleset.hpp>

namespace cro
{
// No ante variant.
inline ruleset make_five_card_draw_ruleset()
{
return ruleset
{
  {
    stage::blind                          ,
    stage::deal_closed_card               ,
    stage::deal_closed_card               ,
    stage::deal_closed_card               ,
    stage::deal_closed_card               ,
    stage::deal_closed_card               ,
    stage::betting_from_left_of_big_blind ,
    stage::deal_replacement_cards         ,
    stage::increase_limit                 ,
    stage::betting_from_left_of_the_button,
    stage::showdown
  },
  std::nullopt               ,
  std::nullopt               ,
  2                          ,
  limit_type::no_limit       ,
  std::nullopt               ,
  std::nullopt               ,
  make_default_hand_ranking(),
  ranking_type::normal       ,
  ace_rule::any              ,
  5                          ,
  std::nullopt                
};
}
}

#endif