#include <croupier/ruleset/holdem/texas_holdem_ruleset.hpp>
#include <croupier/api.hpp>

int main(int argc, char** argv)
{
  const cro::player player_template
  {
    1000,
    [ ] (cro::player* player, cro::table* table, const cro::betting_state& state)
    {
      if (state.bet_to_match())
        return cro::action { cro::action_type::call  };
      else
        return cro::action { cro::action_type::check };

      // TODO: Implement smarter decision function here.
    },
    [ ] (cro::player* player, cro::table* table, std::optional<std::size_t> maximum_cards)
    {
      // TODO: Implement smarter card replacement function here.
      return cro::card_set();
    }
  };

  const cro::game game { cro::make_texas_holdem_ruleset(), cro::table(std::vector<cro::player>(6, player_template)) };
  for (auto i = 0; i < 100; ++i)
    game.dealer.play();

  return 0;
}