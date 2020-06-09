#ifndef CROUPIER_EVALUATOR_EQUIVALENCE_CLASS_HPP
#define CROUPIER_EVALUATOR_EQUIVALENCE_CLASS_HPP

#include <cstddef>
#include <unordered_map>

#include <croupier/card/rank.hpp>
#include <croupier/evaluator/equivalence_class_data.hpp>
#include <croupier/evaluator/hand_evaluation.hpp>
#include <croupier/ruleset/detail/ranking_type.hpp>

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
inline std::unordered_map<std::int32_t, hand_evaluation> make_equivalence_class_map               (const ranking_type& ranking_type = ranking_type::traditional)
{
  auto equivalence_class_map = std::unordered_map<std::int32_t, hand_evaluation>();

  for (auto i = std::uint16_t(0); i < equivalence_class_data.size(); ++i)
  {
    auto type = hand_type_from_string(equivalence_class_data[i][1]);
    auto key  = type == hand_type::flush || type == hand_type::straight_flush ? -1 : 1;
    for (auto& character : equivalence_class_data[i][0])
      key *= rank_to_prime(rank_from_char(character));
    equivalence_class_map[key] = hand_evaluation {type, i};
  }

  // TODO: Re-sort the equivalence classes according to ranking_type; adding support for ace_to_five_low, ace_to_five_high_low, ace_to_six_low, ace_to_six_high_low, badugi.

  return equivalence_class_map;
};

std::unordered_map<std::int32_t, hand_evaluation>        compute_traditional_equivalence_class_map()
{
  auto map = std::unordered_map<std::int32_t, hand_evaluation>();

  // Generate straight flushes.
  for (std::int32_t r1 = rank_count() - 1; r1 >= 5; --r1)
  {
    auto key = -rank_to_prime(rank(r1)) * rank_to_prime(rank(r1 - 1)) * rank_to_prime(rank(r1 - 2)) * rank_to_prime(rank(r1 - 3)) * rank_to_prime(rank(r1 - 4 >= 0 ? r1 - 4 : rank_count() - 1));

    if (map.count(key))
      continue;

    map[key] = hand_evaluation { hand_type::straight_flush, std::uint16_t(map.size()) };
  }

  // Generate four-of-a-kinds.
  for (std::int32_t r1 = rank_count() - 1; r1 >= 0; --r1)
  {
    for (std::int32_t r2 = rank_count() - 1; r2 >= 0; --r2)
    {
      if (r1 == r2)
        continue;

      auto key = std::pow(rank_to_prime(rank(r1)), 4) * rank_to_prime(rank(r2));

      if (map.count(key))
        continue;

      map[key] = hand_evaluation { hand_type::four_of_a_kind, std::uint16_t(map.size()) };
    }
  }

  // Generate full houses.
  for (std::int32_t r1 = rank_count() - 1; r1 >= 0; --r1)
  {
    for (std::int32_t r2 = rank_count() - 1; r2 >= 0; --r2)
    {
      if (r1 == r2)
        continue;

      auto key = std::pow(rank_to_prime(rank(r1)), 3) * std::pow(rank_to_prime(rank(r2)), 2);

      if (map.count(key))
        continue;

      map[key] = hand_evaluation { hand_type::full_house, std::uint16_t(map.size()) };
    }
  }

  // Generate flushes.
  for (std::int32_t r1 = rank_count() - 1; r1 >= 0; --r1)
  {
    for (std::int32_t r2 = rank_count() - 1; r2 >= 0; --r2)
    {
      if (r1 == r2) 
        continue;
      for (std::int32_t r3 = rank_count() - 1; r3 >= 0; --r3)
      {
        if (r1 == r3 || r2 == r3)
          continue;
        for (std::int32_t r4 = rank_count() - 1; r4 >= 0; --r4)
        {
          if (r1 == r4 || r2 == r4 || r3 == r4)
            continue;

          for (std::int32_t r5 = rank_count() - 1; r5 >= 0; --r5)
          {
            if (r1 == r5 || r2 == r5 || r3 == r5 || r4 == r5)
              continue;

            auto key = - rank_to_prime(rank(r1)) * rank_to_prime(rank(r2)) * rank_to_prime(rank(r3)) * rank_to_prime(rank(r4)) * rank_to_prime(rank(r5));

            if (map.count(key))
              continue;

            map[key] = hand_evaluation { hand_type::flush, std::uint16_t(map.size()) };
          }
        }
      }
    }
  }

  // Generate straights.
  for (std::int32_t r1 = rank_count() - 1; r1 >= 5; --r1)
  {
    auto key = rank_to_prime(rank(r1)) * rank_to_prime(rank(r1 - 1)) * rank_to_prime(rank(r1 - 2)) * rank_to_prime(rank(r1 - 3)) * rank_to_prime(rank(r1 - 4 >= 0 ? r1 - 4 : rank_count() - 1));

    if (map.count(key))
      continue;

    map[key] = hand_evaluation { hand_type::straight, std::uint16_t(map.size()) };
  }
  
  // Generate three-of-a-kinds.
  for (std::int32_t r1 = rank_count() - 1; r1 >= 0; --r1)
  {
    for (std::int32_t r2 = rank_count() - 1; r2 >= 0; --r2)
    {
      if (r1 == r2)
        continue;
      for (std::int32_t r3 = rank_count() - 1; r3 >= 0; --r3)
      {
        if (r1 == r3 || r2 == r3)
          continue;

        auto key = std::pow(rank_to_prime(rank(r1)), 3) * rank_to_prime(rank(r2)) * rank_to_prime(rank(r3));

        if (map.count(key))
          continue;

        map[key] = hand_evaluation { hand_type::three_of_a_kind, std::uint16_t(map.size()) };
      }
    }
  }

  // Generate two pairs.
  for (std::int32_t r1 = rank_count() - 1; r1 >= 0; --r1)
  {
    for (std::int32_t r2 = rank_count() - 1; r2 >= 0; --r2)
    {
      if (r1 == r2)
        continue;
      for (std::int32_t r3 = rank_count() - 1; r3 >= 0; --r3)
      {
        if (r1 == r3 || r2 == r3)
          continue;

        auto key = std::pow(rank_to_prime(rank(r1)), 2) * std::pow(rank_to_prime(rank(r2)), 2) * rank_to_prime(rank(r3));

        if (map.count(key))
          continue;

        map[key] = hand_evaluation { hand_type::two_pairs, std::uint16_t(map.size()) };
      }
    }
  }

  // Generate pairs.
  for (std::int32_t r1 = rank_count() - 1; r1 >= 0; --r1)
  {
    for (std::int32_t r2 = rank_count() - 1; r2 >= 0; --r2)
    {
      if (r1 == r2) 
        continue;
      for (std::int32_t r3 = rank_count() - 1; r3 >= 0; --r3)
      {
        if (r1 == r3 || r2 == r3)
          continue;
        for (std::int32_t r4 = rank_count() - 1; r4 >= 0; --r4)
        {
          if (r1 == r4 || r2 == r4 || r3 == r4)
            continue;

          auto key = std::pow(rank_to_prime(rank(r1)), 2) * rank_to_prime(rank(r2)) * rank_to_prime(rank(r3)) * rank_to_prime(rank(r4));

          if (map.count(key))
            continue;

          map[key] = hand_evaluation { hand_type::pair, std::uint16_t(map.size()) };
        }
      }
    }
  }

  // Generate high-cards.
  for (std::int32_t r1 = rank_count() - 1; r1 >= 0; --r1)
  {
    for (std::int32_t r2 = rank_count() - 1; r2 >= 0; --r2)
    {
      if (r1 == r2) 
        continue;
      for (std::int32_t r3 = rank_count() - 1; r3 >= 0; --r3)
      {
        if (r1 == r3 || r2 == r3)
          continue;
        for (std::int32_t r4 = rank_count() - 1; r4 >= 0; --r4)
        {
          if (r1 == r4 || r2 == r4 || r3 == r4)
            continue;

          for (std::int32_t r5 = rank_count() - 1; r5 >= 0; --r5)
          {
            if (r1 == r5 || r2 == r5 || r3 == r5 || r4 == r5)
              continue;

            auto key = rank_to_prime(rank(r1)) * rank_to_prime(rank(r2)) * rank_to_prime(rank(r3)) * rank_to_prime(rank(r4)) * rank_to_prime(rank(r5));

            if (map.count(key))
              continue;

            map[key] = hand_evaluation { hand_type::high_card, std::uint16_t(map.size()) };
          }
        }
      }
    }
  }

  return map;
}
}

#endif
