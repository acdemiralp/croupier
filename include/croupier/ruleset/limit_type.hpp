#ifndef CROUPIER_RULESET_LIMIT_TYPE_HPP
#define CROUPIER_RULESET_LIMIT_TYPE_HPP

#include <cstdint>

namespace cro
{
enum class limit_type : std::uint8_t
{
  no_limit   ,
  pot_limit  ,
  fixed_limit
};
}

#endif