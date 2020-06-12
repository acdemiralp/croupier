#ifndef CROUPIER_EVALUATOR_EQUIVALENCE_CLASS_HPP
#define CROUPIER_EVALUATOR_EQUIVALENCE_CLASS_HPP

#include <cstddef>
#include <cstdint>
#include <unordered_map>

#include <croupier/evaluator/hand_evaluation.hpp>
#include <croupier/ruleset/ranking_type.hpp>

namespace cro
{
// The key to the equivalence class map is computed as:
// - Given the following mapping from ranks to primes:
//   2  3  4  5  6  7  8  9  T  J  Q  K  A 
//   2  3  5  7  11 13 17 19 23 29 31 37 41
// - Multiply the prime of each card rank in card_set.
// - If the card_set is a flush, negate.
//
// Explanation: As stated in the fundamental theorem of arithmetic, any product of primes is unique,
// which ensures each rank is represented independent of one another. The product is further
// independent on the order of the cards, which removes the need for sorting. Flushes are identified
// through negation instead of an additional prime to ensure fitting into the range of a 32-bit integer.

template <ranking_type ranking, std::size_t cards>
struct missing_equivalence_class_implementation : std::false_type {};

template <ranking_type ranking, std::size_t cards>
std::unordered_map<std::int32_t, hand_evaluation> make_equivalence_classes()
{
  static_assert(missing_equivalence_class_implementation<ranking, cards>::value, "Missing equivalence class implementation.");

  return std::unordered_map<std::int32_t, hand_evaluation>();
}
}

#endif
