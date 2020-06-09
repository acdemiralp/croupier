#ifndef CROUPIER_RULESET_RULESET_HPP
#define CROUPIER_RULESET_RULESET_HPP

#include <cstddef>
#include <cstdint>
#include <optional>
#include <vector>

#include <croupier/ruleset/detail/blinds.hpp>
#include <croupier/ruleset/detail/limit_type.hpp>
#include <croupier/ruleset/detail/limits.hpp>
#include <croupier/ruleset/detail/ranking_type.hpp>
#include <croupier/ruleset/detail/stage.hpp>

namespace cro
{
struct ruleset
{
  std::vector<stage>           stages                    = {};

  std::optional<std::uint64_t> ante                      = std::nullopt;
  std::optional<std::uint64_t> bring_in                  = std::nullopt;
  std::optional<blinds>        blinds                    = std::nullopt;

  limit_type                   limit_type                = limit_type::no_limit;
  std::optional<limits>        fixed_limits              = std::nullopt;
  std::optional<std::size_t>   raise_cap                 = 3;

  ranking_type                 ranking_type              = ranking_type::traditional;
  std::size_t                  evaluated_cards           = 5;
  std::optional<std::size_t>   evaluated_community_cards = std::nullopt;

  std::optional<std::size_t>   maximum_replacement_cards = std::nullopt;
};
}

#endif