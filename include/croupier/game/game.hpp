#ifndef CROUPIER_GAME_GAME_HPP
#define CROUPIER_GAME_GAME_HPP

#include <croupier/ruleset/ruleset.hpp>
#include <croupier/game/dealer.hpp>
#include <croupier/game/event.hpp>
#include <croupier/game/table.hpp>

namespace cro
{
// A game consists of a dealer applying a ruleset to a table, recording each event.
struct game
{
  ruleset                         ruleset;
  table                           table  ;
  dealer                          dealer {&ruleset, &table, &history};
  std::vector<std::vector<event>> history;
};
}

#endif