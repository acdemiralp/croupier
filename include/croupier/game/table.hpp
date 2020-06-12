#ifndef CROUPIER_GAME_TABLE_HPP
#define CROUPIER_GAME_TABLE_HPP

#include <map>
#include <optional>
#include <vector>

#include <croupier/card/card_set.hpp>
#include <croupier/card/deck.hpp>
#include <croupier/player/player_set.hpp>
#include <croupier/player/player.hpp>

namespace cro
{
class dealer;
class evaluator;

class table
{
public:
  explicit table  (const std::vector<player>& players = std::vector<player>()) : players_(players), active_players_(players.size()), button_player_(players.size())
  {
    for (auto& player : players_)
      player.table = this;
  }
  table           (const table&  that) = default;
  table           (      table&& temp) = default;
 ~table           ()                   = default;
  table& operator=(const table&  that) = default;
  table& operator=(      table&& temp) = default;

protected:
  friend dealer;
  friend evaluator;
  friend player;
  friend player_set;

  std::vector<player>                 players_;
  player_set                          active_players_;
  player_set                          button_player_;
  deck                                deck_;
  std::map<player_set, std::uint64_t> pots_;
  card_set                            community_cards_;
  std::optional<std::uint64_t>        fixed_limit_;
};

// Delayed implementations to prevent circular includes.
inline             player_set::player_set (const player& player) : bitset_(player.table->players_.size())
{
  bitset_[player.index()] = true;
}
inline std::size_t player::index          () const
{
  return std::distance(table->players_.begin(), std::find_if(table->players_.begin(), table->players_.end(), 
    [this] (const player& iteratee)
    {
      return &iteratee == this;
    }));
}
}

#endif