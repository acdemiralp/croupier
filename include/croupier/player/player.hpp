#ifndef CROUPIER_PLAYER_PLAYER_HPP
#define CROUPIER_PLAYER_PLAYER_HPP

#include <cstddef>
#include <cstdint>
#include <functional>
#include <optional>

#include <croupier/card/card_set.hpp>
#include <croupier/action.hpp>

namespace cro
{
struct betting_state;
class  table;

struct player
{
  std::size_t index() const;

  std::uint64_t                                                        chips                     ;
  std::function<action  (player*, table*, const betting_state&)>       decision_function         ;
  std::function<card_set(player*, table*, std::optional<std::size_t>)> card_replacement_function ;
  table*                                                               table                     = nullptr;
  card_set                                                             open_cards                = card_set();
  card_set                                                             closed_cards              = card_set();
};
}

#endif