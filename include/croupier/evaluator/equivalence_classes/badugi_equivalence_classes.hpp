#ifndef CROUPIER_EVALUATOR_EQUIVALENCE_CLASSES_BADUGI_EQUIVALENCE_CLASSES_HPP
#define CROUPIER_EVALUATOR_EQUIVALENCE_CLASSES_BADUGI_EQUIVALENCE_CLASSES_HPP

#include <croupier/evaluator/equivalence_class.hpp>

namespace cro
{
template <>
inline std::unordered_map<std::int32_t, hand_evaluation> make_equivalence_classes<ranking_type::badugi, 1>()
{
  // TODO
  return std::unordered_map<std::int32_t, hand_evaluation>();
}
template <>
inline std::unordered_map<std::int32_t, hand_evaluation> make_equivalence_classes<ranking_type::badugi, 2>()
{
  // TODO
  return std::unordered_map<std::int32_t, hand_evaluation>();
}
template <>
inline std::unordered_map<std::int32_t, hand_evaluation> make_equivalence_classes<ranking_type::badugi, 3>()
{
  // TODO
  return std::unordered_map<std::int32_t, hand_evaluation>();
}
template <>
inline std::unordered_map<std::int32_t, hand_evaluation> make_equivalence_classes<ranking_type::badugi, 4>()
{
  // TODO
  return std::unordered_map<std::int32_t, hand_evaluation>();
}
}
#endif