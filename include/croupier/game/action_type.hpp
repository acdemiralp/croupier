#ifndef CROUPIER_GAME_ACTION_TYPE_HPP
#define CROUPIER_GAME_ACTION_TYPE_HPP

#include <cstdint>

namespace cro
{
enum class action_type : std::uint8_t
{
  check,
  bet  ,
  call ,
  raise,
  fold
};
}

#endif