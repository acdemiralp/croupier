#ifndef CROUPIER_RULESET_LIMITS_HPP
#define CROUPIER_RULESET_LIMITS_HPP

#include <cstdint>

namespace cro
{
struct limits
{
  std::uint64_t small_bet = 1; // Before limit increase stage.
  std::uint64_t big_bet   = 2; // After  limit increase stage.
};
}

#endif