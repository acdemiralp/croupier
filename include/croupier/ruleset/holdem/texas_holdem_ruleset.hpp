#ifndef CROUPIER_RULESET_HOLDEM_TEXAS_HOLDEM_RULESET_HPP
#define CROUPIER_RULESET_HOLDEM_TEXAS_HOLDEM_RULESET_HPP

#include <croupier/ruleset/ruleset.hpp>

namespace cro
{
inline ruleset make_texas_holdem_ruleset()
{
return ruleset
{
  {
    stage::deal_closed_card               ,
    stage::deal_closed_card               ,
    stage::blind                          ,
    stage::burn_card                      ,
    stage::deal_community_card            ,
    stage::deal_community_card            ,
    stage::deal_community_card            ,
    stage::betting_from_left_of_the_button,
    stage::burn_card                      ,
    stage::deal_community_card            ,
    stage::increase_limit                 ,
    stage::betting_from_left_of_the_button,
    stage::burn_card                      ,
    stage::deal_community_card            ,
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