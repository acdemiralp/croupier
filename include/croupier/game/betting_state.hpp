#ifndef CROUPIER_GAME_BETTING_STATE_HPP
#define CROUPIER_GAME_BETTING_STATE_HPP

#include <cstddef>
#include <cstdint>
#include <optional>
#include <vector>

#include <croupier/player/player_set.hpp>

namespace cro
{
struct betting_state
{
  explicit betting_state  (const player_set& active_players)
  : complying_players(active_players.size())
  , bet_amounts      (active_players.size(), 0)
  {

  }
  betting_state           (const betting_state&  that) = default;
  betting_state           (      betting_state&& temp) = default;
 ~betting_state           ()                   = default;
  betting_state& operator=(const betting_state&  that) = default;
  betting_state& operator=(      betting_state&& temp) = default;

  player_set                   complying_players;
  std::vector  <std::uint64_t> bet_amounts      ;
  std::optional<std::uint64_t> bet_to_match     = std::nullopt;
  std::size_t                  raises           = 0;
};
}

#endif