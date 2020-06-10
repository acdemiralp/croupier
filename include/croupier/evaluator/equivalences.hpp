#ifndef CROUPIER_EVALUATOR_EQUIVALENCES_HPP
#define CROUPIER_EVALUATOR_EQUIVALENCES_HPP

#include <cstddef>
#include <cstdint>
#include <unordered_map>

#include <croupier/evaluator/equivalence_classes/ace_to_five_low_equivalence_classes.hpp>
#include <croupier/evaluator/equivalence_classes/ace_to_six_low_equivalence_classes.hpp>
#include <croupier/evaluator/equivalence_classes/deuce_to_seven_low_equivalence_classes.hpp>
#include <croupier/evaluator/equivalence_classes/traditional_equivalence_classes.hpp>
#include <croupier/evaluator/hand_evaluation.hpp>
#include <croupier/ruleset/ranking_type.hpp>

namespace cro
{
// Maps ranking type to the number of evaluated cards to the equivalence classes.
using equivalences = std::unordered_map<ranking_type, std::unordered_map<std::size_t, std::unordered_map<std::int32_t, hand_evaluation>>>;

inline equivalences make_equivalences()
{
  equivalences equivalences;

  equivalences[ranking_type::traditional]       [1] = make_equivalence_classes<ranking_type::traditional       , 1>();
  equivalences[ranking_type::traditional]       [2] = make_equivalence_classes<ranking_type::traditional       , 2>();
  equivalences[ranking_type::traditional]       [3] = make_equivalence_classes<ranking_type::traditional       , 3>();
  equivalences[ranking_type::traditional]       [4] = make_equivalence_classes<ranking_type::traditional       , 4>();
  equivalences[ranking_type::traditional]       [5] = make_equivalence_classes<ranking_type::traditional       , 5>();
                                                                                                               
  equivalences[ranking_type::ace_to_five_low]   [1] = make_equivalence_classes<ranking_type::ace_to_five_low   , 1>();
  equivalences[ranking_type::ace_to_five_low]   [2] = make_equivalence_classes<ranking_type::ace_to_five_low   , 2>();
  equivalences[ranking_type::ace_to_five_low]   [3] = make_equivalence_classes<ranking_type::ace_to_five_low   , 3>();
  equivalences[ranking_type::ace_to_five_low]   [4] = make_equivalence_classes<ranking_type::ace_to_five_low   , 4>();
  equivalences[ranking_type::ace_to_five_low]   [5] = make_equivalence_classes<ranking_type::ace_to_five_low   , 5>();
                                                                                                               
  equivalences[ranking_type::ace_to_six_low]    [1] = make_equivalence_classes<ranking_type::ace_to_six_low    , 1>();
  equivalences[ranking_type::ace_to_six_low]    [2] = make_equivalence_classes<ranking_type::ace_to_six_low    , 2>();
  equivalences[ranking_type::ace_to_six_low]    [3] = make_equivalence_classes<ranking_type::ace_to_six_low    , 3>();
  equivalences[ranking_type::ace_to_six_low]    [4] = make_equivalence_classes<ranking_type::ace_to_six_low    , 4>();
  equivalences[ranking_type::ace_to_six_low]    [5] = make_equivalence_classes<ranking_type::ace_to_six_low    , 5>();

  equivalences[ranking_type::deuce_to_seven_low][1] = make_equivalence_classes<ranking_type::deuce_to_seven_low, 1>();
  equivalences[ranking_type::deuce_to_seven_low][2] = make_equivalence_classes<ranking_type::deuce_to_seven_low, 2>();
  equivalences[ranking_type::deuce_to_seven_low][3] = make_equivalence_classes<ranking_type::deuce_to_seven_low, 3>();
  equivalences[ranking_type::deuce_to_seven_low][4] = make_equivalence_classes<ranking_type::deuce_to_seven_low, 4>();
  equivalences[ranking_type::deuce_to_seven_low][5] = make_equivalence_classes<ranking_type::deuce_to_seven_low, 5>();

  return equivalences;
}
}

#endif
