#ifndef CROUPIER_RULESET_STUD_RAZZ_RULESET_HPP
#define CROUPIER_RULESET_STUD_RAZZ_RULESET_HPP

#include <croupier/ruleset/ruleset.hpp>

namespace cro
{
inline ruleset make_razz_ruleset()
{
return ruleset
{
  {
    stage::ante                             ,
    stage::deal_closed_card                 ,
    stage::deal_closed_card                 ,
    stage::deal_open_card                   ,
    stage::bring_in_from_highest_open       ,
    stage::deal_open_card                   , // Fourth  street.
    stage::betting_from_left_of_lowest_open ,
    stage::deal_open_card                   , // Fifth   street.
    stage::increase_limit                   ,
    stage::betting_from_left_of_lowest_open ,
    stage::deal_open_card                   , // Sixth   street.
    stage::betting_from_left_of_lowest_open ,
    stage::deal_closed_card                 , // Seventh street.
    stage::betting_from_left_of_lowest_open ,
    stage::showdown
  },
  1                      ,
  2                      ,
  std::nullopt           ,
  limit_type::fixed_limit,
  limits {2, 4}          ,
  3                      ,
  ranking_type::ace_to_five_low
};
}
}

#endif