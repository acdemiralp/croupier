#ifndef CROUPIER_RULESET_DETAIL_STAGE_HPP
#define CROUPIER_RULESET_DETAIL_STAGE_HPP

#include <cstdint>

namespace cro
{
enum class stage : std::uint8_t
{
  ante                             ,
  betting_from_left_of_the_button  ,
  betting_from_left_of_big_blind   ,
  betting_from_left_of_lowest_open ,  
  betting_from_left_of_highest_open, 
  blind                            ,
  bring_in_from_lowest_open        ,
  bring_in_from_highest_open       ,
  burn_card                        ,
  deal_closed_card                 ,
  deal_community_card              ,
  deal_open_card                   ,
  deal_replacement_cards           ,
  increase_limit                   ,
  showdown
};
}

#endif