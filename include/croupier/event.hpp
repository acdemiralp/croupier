#ifndef CROUPIER_EVENT_HPP
#define CROUPIER_EVENT_HPP

#include <cstdint>
#include <optional>

#include <croupier/card/card_set.hpp>
#include <croupier/player/player_set.hpp>
#include <croupier/event_type.hpp>

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