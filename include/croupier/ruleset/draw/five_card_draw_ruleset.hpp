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
    stage::deal_closed_card               ,
    stage::deal_closed_card               ,
    stage::deal_closed_card               ,
    stage::deal_closed_card               ,
    stage::deal_closed_card               ,
    stage::blind                          ,
    stage::deal_replacement_cards         ,
    stage::increase_limit                 ,
    stage::betting_from_left_of_the_button,
    stage::showdown
  },
  std::nullopt,
  std::nullopt,
  blinds {1, 2}            
};
}
}

#endif