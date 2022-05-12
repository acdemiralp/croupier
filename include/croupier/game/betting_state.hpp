#ifndef CROUPIER_GAME_BETTING_STATE_HPP
#define CROUPIER_GAME_BETTING_STATE_HPP

#include <cstddef>
#include <cstdint>
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
  betting_state           (const betting_state&  that)          = default;
  betting_state           (      betting_state&& temp) noexcept = default;
 ~betting_state           ()                                    = default;
  betting_state& operator=(const betting_state&  that)          = default;
  betting_state& operator=(      betting_state&& temp) noexcept = default;

  [[nodiscard]]
  std::uint64_t bet_to_match() const
  {
    return *std::max_element(bet_amounts.begin(), bet_amounts.end());
  }

  player_set                 complying_players;
  std::vector<std::uint64_t> bet_amounts      ;
  std::size_t                raises           = 0;
};
}

#endif