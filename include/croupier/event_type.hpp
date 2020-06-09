#ifndef CROUPIER_EVENT_TYPE_HPP
#define CROUPIER_EVENT_TYPE_HPP

#include <cstdint>

namespace cro
{
// Enum containing both the action_type and stage. Bad practice. Used only for logging.
enum class event_type : std::uint8_t
{
  ante                           , // player_set(N)             chips
  betting_from_left_of_the_button, // player_set(1)             
  betting_from_left_of_big_blind , // player_set(1)             
  betting_from_lowest_open_card  , // player_set(1) card_set(N) 
  betting_from_highest_open_card , // player_set(1) card_set(N) 
  blind                          , // player_set(1)             chips
  bring_in_from_lowest_open_card , // player_set(1) card_set(N) chips
  bring_in_from_highest_open_card, // player_set(1) card_set(N) chips
  burn_card                      , //               card_set(1) 
  deal_closed_card               , // player_set(1) card_set(1) 
  deal_community_card            , //               card_set(1) 
  deal_open_card                 , // player_set(1) card_set(1) 
  deal_replacement_cards         , // player_set(1) card_set(N)  
  increase_limit                 , //                           chips
  showdown                       , // player_set(1)             chips

  check                          , // player_set(1)
  bet                            , // player_set(1)             chips
  call                           , // player_set(1)             chips
  raise                          , // player_set(1)             chips
  fold                           , // player_set(1)
};
}

#endif