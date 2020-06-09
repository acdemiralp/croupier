#ifndef CROUPIER_RULESET_STUD_SEVEN_CARD_STUD_RULESET_HPP
#define CROUPIER_RULESET_STUD_SEVEN_CARD_STUD_RULESET_HPP

#include <croupier/ruleset/ruleset.hpp>

namespace cro
{
inline ruleset make_seven_card_stud_ruleset()
{
return ruleset
{
  {
    stage::ante                             ,
    stage::deal_closed_card                 ,
    stage::deal_closed_card                 ,
    stage::deal_open_card                   ,
    stage::bring_in_from_lowest_open        ,
    stage::deal_open_card                   , // Fourth  street.
    stage::betting_from_left_of_highest_open,
    stage::deal_open_card                   , // Fifth   street.
    stage::increase_limit                   ,
    stage::betting_from_left_of_highest_open,
    stage::deal_open_card                   , // Sixth   street.
    stage::betting_from_left_of_highest_open,
    stage::deal_closed_card                 , // Seventh street.
    stage::betting_from_left_of_highest_open,
    stage::showdown
  },
  1                        ,
  2                        ,
  std::nullopt             ,
  limit_type::fixed_limit  ,
  limits {2, 4}
};
}
}

#endif