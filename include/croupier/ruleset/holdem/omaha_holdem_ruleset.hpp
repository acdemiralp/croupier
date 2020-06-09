#ifndef CROUPIER_RULESET_HOLDEM_OMAHA_HOLDEM_RULESET_HPP
#define CROUPIER_RULESET_HOLDEM_OMAHA_HOLDEM_RULESET_HPP

#include <croupier/ruleset/ruleset.hpp>

namespace cro
{
inline ruleset make_omaha_holdem_ruleset()
{
return ruleset
{
  {
    stage::blind                          ,
    stage::deal_closed_card               ,
    stage::deal_closed_card               ,
    stage::deal_closed_card               ,
    stage::deal_closed_card               ,
    stage::betting_from_left_of_big_blind ,
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
  std::nullopt             ,
  std::nullopt             ,
  blinds {1, 2}            ,
  limit_type::fixed_limit  ,
  limits {2, 4}            ,
  3                        ,
  ranking_type::traditional,
  5,
  3
};
}
}

#endif