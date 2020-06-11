#ifndef CROUPIER_RULESET_STAGE_HPP
#define CROUPIER_RULESET_STAGE_HPP

#include <cstdint>

namespace cro
{
enum class stage : std::uint8_t
{
  ante                           ,
  betting_from_left_of_the_button,
  betting_from_best_open         ,  
  betting_from_worst_open        , 
  blind                          ,
  bring_in                       ,
  burn_card                      ,
  deal_closed_card               ,
  deal_community_card            ,
  deal_open_card                 ,
  deal_replacement_cards         ,
  increase_limit                 ,
  showdown
};
}

#endif