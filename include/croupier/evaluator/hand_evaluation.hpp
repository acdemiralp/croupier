#ifndef CROUPIER_EVALUATOR_HAND_EVALUATION_HPP
#define CROUPIER_EVALUATOR_HAND_EVALUATION_HPP

#include <cstdint>

#include <croupier/evaluator/hand_type.hpp>

namespace cro
{
// A compacter version is possible through a 3:13 bit field, but the space gain is negligible for ~7462 entries.
struct hand_evaluation
{
  bool operator< (const hand_evaluation& that) const
  {
    return equivalence_class < that.equivalence_class;
  }
  bool operator==(const hand_evaluation& that) const
  {
    return equivalence_class == that.equivalence_class;
  }

  hand_type     type;
  std::uint16_t equivalence_class;
};
}

#endif