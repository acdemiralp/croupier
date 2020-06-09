#ifndef CROUPIER_ACTION_HPP
#define CROUPIER_ACTION_HPP

#include <cstdint>
#include <optional>

#include <croupier/action_type.hpp>

namespace cro
{
struct action
{
  action_type                  type  ;
  std::optional<std::uint64_t> value = std::nullopt;
};
}

#endif