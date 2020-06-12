#ifndef CROUPIER_GAME_EVENT_HPP
#define CROUPIER_GAME_EVENT_HPP

#include <cstdint>
#include <optional>

#include <croupier/card/card_set.hpp>
#include <croupier/game/event_type.hpp>
#include <croupier/player/player_set.hpp>

namespace cro
{
struct event
{
  event_type                   type       ;
  std::optional<player_set>    player_set = std::nullopt;
  std::optional<card_set>      card_set   = std::nullopt;
  std::optional<std::uint64_t> chips      = std::nullopt;
};
}

#endif