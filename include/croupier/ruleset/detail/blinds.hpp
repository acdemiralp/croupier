#ifndef CROUPIER_RULESET_DETAIL_BLINDS_HPP
#define CROUPIER_RULESET_DETAIL_BLINDS_HPP

#include <cstdint>

namespace cro
{
struct blinds
{
  std::uint64_t small_blind = 1;
  std::uint64_t big_blind   = 2;
};
}

#endif