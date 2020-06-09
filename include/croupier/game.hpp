#ifndef CROUPIER_GAME_HPP
#define CROUPIER_GAME_HPP

#include <croupier/ruleset/ruleset.hpp>
#include <croupier/dealer.hpp>
#include <croupier/round.hpp>
#include <croupier/table.hpp>

namespace cro
{
// A game consists of a dealer applying a ruleset to a table, recording each event.
struct game
{
  dealer             dealer {&ruleset, &table, &history};
  ruleset            ruleset;
  table              table  ;
  std::vector<round> history;
};
}

#endif