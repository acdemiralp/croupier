#ifndef CROUPIER_RULESET_DETAIL_RANKING_TYPE_HPP
#define CROUPIER_RULESET_DETAIL_RANKING_TYPE_HPP

#include <cstdint>

namespace cro
{
enum class ranking_type : std::uint8_t
{
  traditional            , // Aces are high or low.
  //ace_to_five_low        , // Aces are low  in low hands. No straights or flushes.
  //ace_to_five_high_low   , // Aces are low  in low hands. No straights or flushes.
  //ace_to_six_low         , // Aces are low  in low hands.
  //ace_to_six_high_low    , // Aces are low  in low hands.
  deuce_to_seven_low     , // Aces are high in low hands. Exact inverse of traditional.
  deuce_to_seven_high_low, // Aces are high in low hands. Exact inverse of traditional.
  //badugi
};
}

#endif