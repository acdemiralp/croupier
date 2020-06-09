#ifndef CROUPIER_EVALUATOR_EQUIVALENCE_CLASS_HPP
#define CROUPIER_EVALUATOR_EQUIVALENCE_CLASS_HPP

#include <cstdint>
#include <stdexcept>
#include <unordered_map>

#include <croupier/card/rank.hpp>
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
inline std::unordered_map<std::int32_t, hand_evaluation> make_traditional_equivalence_classes       ()
{
  auto map       = std::unordered_map<std::int32_t, hand_evaluation>();
  auto ranks     = std::vector<rank>
  {
    rank::A ,
    rank::K ,
    rank::Q ,
    rank::J ,
    rank::T ,
    rank::_9,
    rank::_8,
    rank::_7,
    rank::_6,
    rank::_5,
    rank::_4,
    rank::_3,
    rank::_2
  };
  auto straights = std::vector<rank>
  {
    rank::A ,
    rank::K ,
    rank::Q ,
    rank::J ,
    rank::T ,
    rank::_9,
    rank::_8,
    rank::_7,
    rank::_6,
    rank::_5,
  };
  
  // Generate straight flushes.
  for (auto& r1 : straights)
  {
    const auto key = 
      - rank_to_prime(r1)
      * rank_to_prime(rank((std::int32_t(r1) - 1 + rank_count()) % rank_count()))
      * rank_to_prime(rank((std::int32_t(r1) - 2 + rank_count()) % rank_count()))
      * rank_to_prime(rank((std::int32_t(r1) - 3 + rank_count()) % rank_count()))
      * rank_to_prime(rank((std::int32_t(r1) - 4 + rank_count()) % rank_count()));
    if (!map.count(key))
      map[key] = hand_evaluation { hand_type::straight_flush, std::uint16_t(map.size()) };
  }

  // Generate four-of-a-kinds.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;

      const auto key = std::pow(rank_to_prime(r1), 4) * rank_to_prime(r2);
      if (!map.count(key))
        map[key] = hand_evaluation { hand_type::four_of_a_kind, std::uint16_t(map.size()) };
    }
  }

  // Generate full houses.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;

      const auto key = std::pow(rank_to_prime(r1), 3) * std::pow(rank_to_prime(r2), 2);
      if (!map.count(key))
        map[key] = hand_evaluation { hand_type::full_house, std::uint16_t(map.size()) };
    }
  }

  // Generate flushes.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;
      for (auto& r3 : ranks)
      {
        if (r1 == r3 || r2 == r3) continue;
        for (auto& r4 : ranks)
        {
          if (r1 == r4 || r2 == r4 || r3 == r4) continue;
          for (auto& r5 : ranks)
          {
            if (r1 == r5 || r2 == r5 || r3 == r5 || r4 == r5) continue;

            const auto key = - rank_to_prime(r1) * rank_to_prime(r2) * rank_to_prime(r3) * rank_to_prime(r4) * rank_to_prime(r5);
            if (!map.count(key))
              map[key] = hand_evaluation { hand_type::flush, std::uint16_t(map.size()) };
          }
        }
      }
    }
  }

  // Generate straights.
  for (auto& r1 : straights)
  {
    const auto key = 
        rank_to_prime(r1)
      * rank_to_prime(rank((std::int32_t(r1) - 1 + rank_count()) % rank_count()))
      * rank_to_prime(rank((std::int32_t(r1) - 2 + rank_count()) % rank_count()))
      * rank_to_prime(rank((std::int32_t(r1) - 3 + rank_count()) % rank_count()))
      * rank_to_prime(rank((std::int32_t(r1) - 4 + rank_count()) % rank_count()));
    if (!map.count(key))
      map[key] = hand_evaluation { hand_type::straight, std::uint16_t(map.size()) };
  }
  
  // Generate three-of-a-kinds.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;
      for (auto& r3 : ranks)
      {
        if (r1 == r3 || r2 == r3) continue;

        const auto key = std::pow(rank_to_prime(r1), 3) * rank_to_prime(r2) * rank_to_prime(r3);
        if (!map.count(key))
          map[key] = hand_evaluation { hand_type::three_of_a_kind, std::uint16_t(map.size()) };
      }
    }
  }

  // Generate two pairs.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;
      for (auto& r3 : ranks)
      {
        if (r1 == r3 || r2 == r3) continue;

        const auto key = std::pow(rank_to_prime(r1), 2) * std::pow(rank_to_prime(r2), 2) * rank_to_prime(r3);
        if (!map.count(key))
          map[key] = hand_evaluation { hand_type::two_pairs, std::uint16_t(map.size()) };
      }
    }
  }

  // Generate pairs.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;
      for (auto& r3 : ranks)
      {
        if (r1 == r3 || r2 == r3) continue;
        for (auto& r4 : ranks)
        {
          if (r1 == r4 || r2 == r4 || r3 == r4) continue;

          const auto key = std::pow(rank_to_prime(r1), 2) * rank_to_prime(r2) * rank_to_prime(r3) * rank_to_prime(r4);
          if (!map.count(key))
            map[key] = hand_evaluation { hand_type::pair, std::uint16_t(map.size()) };
        }
      }
    }
  }

  // Generate high-cards.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;
      for (auto& r3 : ranks)
      {
        if (r1 == r3 || r2 == r3) continue;
        for (auto& r4 : ranks)
        {
          if (r1 == r4 || r2 == r4 || r3 == r4) continue;
          for (auto& r5 : ranks)
          {
            if (r1 == r5 || r2 == r5 || r3 == r5 || r4 == r5) continue;

            const auto key = rank_to_prime(r1) * rank_to_prime(r2) * rank_to_prime(r3) * rank_to_prime(r4) * rank_to_prime(r5);
            if (!map.count(key))
              map[key] = hand_evaluation { hand_type::high_card, std::uint16_t(map.size()) };
          }
        }
      }
    }
  }

  return map;
}
inline std::unordered_map<std::int32_t, hand_evaluation> make_ace_to_five_low_equivalence_classes   ()
{
  auto map   = std::unordered_map<std::int32_t, hand_evaluation>();
  auto ranks = std::vector<rank>
  {
    rank::A ,
    rank::_2,
    rank::_3,
    rank::_4,
    rank::_5,
    rank::_6,
    rank::_7,
    rank::_8,
    rank::_9,
    rank::T ,
    rank::J ,
    rank::Q ,
    rank::K
  };
  
  // Generate high-cards.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;
      for (auto& r3 : ranks)
      {
        if (r1 == r3 || r2 == r3) continue;
        for (auto& r4 : ranks)
        {
          if (r1 == r4 || r2 == r4 || r3 == r4) continue;
          for (auto& r5 : ranks)
          {
            if (r1 == r5 || r2 == r5 || r3 == r5 || r4 == r5) continue;

            const auto key = rank_to_prime(r1) * rank_to_prime(r2) * rank_to_prime(r3) * rank_to_prime(r4) * rank_to_prime(r5);
            if (!map.count(key))
              map[key] = hand_evaluation { hand_type::high_card, std::uint16_t(map.size()) };
          }
        }
      }
    }
  }

  // Generate pairs.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;
      for (auto& r3 : ranks)
      {
        if (r1 == r3 || r2 == r3) continue;
        for (auto& r4 : ranks)
        {
          if (r1 == r4 || r2 == r4 || r3 == r4) continue;

          const auto key = std::pow(rank_to_prime(r1), 2) * rank_to_prime(r2) * rank_to_prime(r3) * rank_to_prime(r4);
          if (!map.count(key))
            map[key] = hand_evaluation { hand_type::pair, std::uint16_t(map.size()) };
        }
      }
    }
  }

  // Generate two pairs.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;
      for (auto& r3 : ranks)
      {
        if (r1 == r3 || r2 == r3) continue;

        const auto key = std::pow(rank_to_prime(r1), 2) * std::pow(rank_to_prime(r2), 2) * rank_to_prime(r3);
        if (!map.count(key))
          map[key] = hand_evaluation { hand_type::two_pairs, std::uint16_t(map.size()) };
      }
    }
  }

  // Generate three-of-a-kinds.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;
      for (auto& r3 : ranks)
      {
        if (r1 == r3 || r2 == r3) continue;

        const auto key = std::pow(rank_to_prime(r1), 3) * rank_to_prime(r2) * rank_to_prime(r3);
        if (!map.count(key))
          map[key] = hand_evaluation { hand_type::three_of_a_kind, std::uint16_t(map.size()) };
      }
    }
  }

  // Generate full houses.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;

      const auto key = std::pow(rank_to_prime(r1), 3) * std::pow(rank_to_prime(r2), 2);
      if (!map.count(key))
        map[key] = hand_evaluation { hand_type::full_house, std::uint16_t(map.size()) };
    }
  }

  // Generate four-of-a-kinds.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;

      const auto key = std::pow(rank_to_prime(r1), 4) * rank_to_prime(r2);
      if (!map.count(key))
        map[key] = hand_evaluation { hand_type::four_of_a_kind, std::uint16_t(map.size()) };
    }
  }

  return map;
}
inline std::unordered_map<std::int32_t, hand_evaluation> make_ace_to_six_low_equivalence_classes    ()
{
  auto map       = std::unordered_map<std::int32_t, hand_evaluation>();
  auto ranks     = std::vector<rank>
  {
    rank::A ,
    rank::_2,
    rank::_3,
    rank::_4,
    rank::_5,
    rank::_6,
    rank::_7,
    rank::_8,
    rank::_9,
    rank::T ,
    rank::J ,
    rank::Q ,
    rank::K
  };
  auto straights = std::vector<rank>
  {
    rank::_5,
    rank::_6,
    rank::_7,
    rank::_8,
    rank::_9,
    rank::T ,
    rank::J ,
    rank::Q ,
    rank::K
  };
  
  // Generate high-cards.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;
      for (auto& r3 : ranks)
      {
        if (r1 == r3 || r2 == r3) continue;
        for (auto& r4 : ranks)
        {
          if (r1 == r4 || r2 == r4 || r3 == r4) continue;
          for (auto& r5 : ranks)
          {
            if (r1 == r5 || r2 == r5 || r3 == r5 || r4 == r5) continue;

            const auto key = rank_to_prime(r1) * rank_to_prime(r2) * rank_to_prime(r3) * rank_to_prime(r4) * rank_to_prime(r5);
            if (!map.count(key))
              map[key] = hand_evaluation { hand_type::high_card, std::uint16_t(map.size()) };
          }
        }
      }
    }
  }

  // Generate pairs.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;
      for (auto& r3 : ranks)
      {
        if (r1 == r3 || r2 == r3) continue;
        for (auto& r4 : ranks)
        {
          if (r1 == r4 || r2 == r4 || r3 == r4) continue;

          const auto key = std::pow(rank_to_prime(r1), 2) * rank_to_prime(r2) * rank_to_prime(r3) * rank_to_prime(r4);
          if (!map.count(key))
            map[key] = hand_evaluation { hand_type::pair, std::uint16_t(map.size()) };
        }
      }
    }
  }

  // Generate two pairs.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;
      for (auto& r3 : ranks)
      {
        if (r1 == r3 || r2 == r3) continue;

        const auto key = std::pow(rank_to_prime(r1), 2) * std::pow(rank_to_prime(r2), 2) * rank_to_prime(r3);
        if (!map.count(key))
          map[key] = hand_evaluation { hand_type::two_pairs, std::uint16_t(map.size()) };
      }
    }
  }

  // Generate three-of-a-kinds.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;
      for (auto& r3 : ranks)
      {
        if (r1 == r3 || r2 == r3) continue;

        const auto key = std::pow(rank_to_prime(r1), 3) * rank_to_prime(r2) * rank_to_prime(r3);
        if (!map.count(key))
          map[key] = hand_evaluation { hand_type::three_of_a_kind, std::uint16_t(map.size()) };
      }
    }
  }

  // Generate straights.
  for (auto& r1 : straights)
  {
    const auto key = 
        rank_to_prime(r1)
      * rank_to_prime(rank((std::int32_t(r1) - 1 + rank_count()) % rank_count()))
      * rank_to_prime(rank((std::int32_t(r1) - 2 + rank_count()) % rank_count()))
      * rank_to_prime(rank((std::int32_t(r1) - 3 + rank_count()) % rank_count()))
      * rank_to_prime(rank((std::int32_t(r1) - 4 + rank_count()) % rank_count()));
    // if (!map.count(key)) Overwrite high cards.
      map[key] = hand_evaluation { hand_type::straight, std::uint16_t(map.size()) };
  }
  
  // Generate flushes.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;
      for (auto& r3 : ranks)
      {
        if (r1 == r3 || r2 == r3) continue;
        for (auto& r4 : ranks)
        {
          if (r1 == r4 || r2 == r4 || r3 == r4) continue;
          for (auto& r5 : ranks)
          {
            if (r1 == r5 || r2 == r5 || r3 == r5 || r4 == r5) continue;

            const auto key = - rank_to_prime(r1) * rank_to_prime(r2) * rank_to_prime(r3) * rank_to_prime(r4) * rank_to_prime(r5);
            if (!map.count(key))
              map[key] = hand_evaluation { hand_type::flush, std::uint16_t(map.size()) };
          }
        }
      }
    }
  }

  // Generate full houses.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;

      const auto key = std::pow(rank_to_prime(r1), 3) * std::pow(rank_to_prime(r2), 2);
      if (!map.count(key))
        map[key] = hand_evaluation { hand_type::full_house, std::uint16_t(map.size()) };
    }
  }

  // Generate four-of-a-kinds.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;

      const auto key = std::pow(rank_to_prime(r1), 4) * rank_to_prime(r2);
      if (!map.count(key))
        map[key] = hand_evaluation { hand_type::four_of_a_kind, std::uint16_t(map.size()) };
    }
  }

  // Generate straight flushes.
  for (auto& r1 : straights)
  {
    const auto key = 
      - rank_to_prime(r1)
      * rank_to_prime(rank((std::int32_t(r1) - 1 + rank_count()) % rank_count()))
      * rank_to_prime(rank((std::int32_t(r1) - 2 + rank_count()) % rank_count()))
      * rank_to_prime(rank((std::int32_t(r1) - 3 + rank_count()) % rank_count()))
      * rank_to_prime(rank((std::int32_t(r1) - 4 + rank_count()) % rank_count()));
    // if (!map.count(key)) Overwrite flushes.
      map[key] = hand_evaluation { hand_type::straight_flush, std::uint16_t(map.size()) };
  }

  return map;
}
inline std::unordered_map<std::int32_t, hand_evaluation> make_deuce_to_seven_low_equivalence_classes()
{
  auto map       = std::unordered_map<std::int32_t, hand_evaluation>();
  auto ranks     = std::vector<rank>
  {
    rank::_2,
    rank::_3,
    rank::_4,
    rank::_5,
    rank::_6,
    rank::_7,
    rank::_8,
    rank::_9,
    rank::T ,
    rank::J ,
    rank::Q ,
    rank::K ,
    rank::A
  };
  auto straights = std::vector<rank>
  {
    rank::_6,
    rank::_7,
    rank::_8,
    rank::_9,
    rank::T ,
    rank::J ,
    rank::Q ,
    rank::K ,
    rank::A
  };
  
  // Generate high-cards.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;
      for (auto& r3 : ranks)
      {
        if (r1 == r3 || r2 == r3) continue;
        for (auto& r4 : ranks)
        {
          if (r1 == r4 || r2 == r4 || r3 == r4) continue;
          for (auto& r5 : ranks)
          {
            if (r1 == r5 || r2 == r5 || r3 == r5 || r4 == r5) continue;

            const auto key = rank_to_prime(r1) * rank_to_prime(r2) * rank_to_prime(r3) * rank_to_prime(r4) * rank_to_prime(r5);
            if (!map.count(key))
              map[key] = hand_evaluation { hand_type::high_card, std::uint16_t(map.size()) };
          }
        }
      }
    }
  }

  // Generate pairs.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;
      for (auto& r3 : ranks)
      {
        if (r1 == r3 || r2 == r3) continue;
        for (auto& r4 : ranks)
        {
          if (r1 == r4 || r2 == r4 || r3 == r4) continue;

          const auto key = std::pow(rank_to_prime(r1), 2) * rank_to_prime(r2) * rank_to_prime(r3) * rank_to_prime(r4);
          if (!map.count(key))
            map[key] = hand_evaluation { hand_type::pair, std::uint16_t(map.size()) };
        }
      }
    }
  }

  // Generate two pairs.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;
      for (auto& r3 : ranks)
      {
        if (r1 == r3 || r2 == r3) continue;

        const auto key = std::pow(rank_to_prime(r1), 2) * std::pow(rank_to_prime(r2), 2) * rank_to_prime(r3);
        if (!map.count(key))
          map[key] = hand_evaluation { hand_type::two_pairs, std::uint16_t(map.size()) };
      }
    }
  }

  // Generate three-of-a-kinds.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;
      for (auto& r3 : ranks)
      {
        if (r1 == r3 || r2 == r3) continue;

        const auto key = std::pow(rank_to_prime(r1), 3) * rank_to_prime(r2) * rank_to_prime(r3);
        if (!map.count(key))
          map[key] = hand_evaluation { hand_type::three_of_a_kind, std::uint16_t(map.size()) };
      }
    }
  }

  // Generate straights.
  for (auto& r1 : straights)
  {
    const auto key = 
        rank_to_prime(r1)
      * rank_to_prime(rank((std::int32_t(r1) - 1 + rank_count()) % rank_count()))
      * rank_to_prime(rank((std::int32_t(r1) - 2 + rank_count()) % rank_count()))
      * rank_to_prime(rank((std::int32_t(r1) - 3 + rank_count()) % rank_count()))
      * rank_to_prime(rank((std::int32_t(r1) - 4 + rank_count()) % rank_count()));
    // if (!map.count(key)) Overwrite high cards.
      map[key] = hand_evaluation { hand_type::straight, std::uint16_t(map.size()) };
  }
  
  // Generate flushes.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;
      for (auto& r3 : ranks)
      {
        if (r1 == r3 || r2 == r3) continue;
        for (auto& r4 : ranks)
        {
          if (r1 == r4 || r2 == r4 || r3 == r4) continue;
          for (auto& r5 : ranks)
          {
            if (r1 == r5 || r2 == r5 || r3 == r5 || r4 == r5) continue;

            const auto key = - rank_to_prime(r1) * rank_to_prime(r2) * rank_to_prime(r3) * rank_to_prime(r4) * rank_to_prime(r5);
            if (!map.count(key))
              map[key] = hand_evaluation { hand_type::flush, std::uint16_t(map.size()) };
          }
        }
      }
    }
  }

  // Generate full houses.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;

      const auto key = std::pow(rank_to_prime(r1), 3) * std::pow(rank_to_prime(r2), 2);
      if (!map.count(key))
        map[key] = hand_evaluation { hand_type::full_house, std::uint16_t(map.size()) };
    }
  }

  // Generate four-of-a-kinds.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;

      const auto key = std::pow(rank_to_prime(r1), 4) * rank_to_prime(r2);
      if (!map.count(key))
        map[key] = hand_evaluation { hand_type::four_of_a_kind, std::uint16_t(map.size()) };
    }
  }

  // Generate straight flushes.
  for (auto& r1 : straights)
  {
    const auto key = 
      - rank_to_prime(r1)
      * rank_to_prime(rank((std::int32_t(r1) - 1 + rank_count()) % rank_count()))
      * rank_to_prime(rank((std::int32_t(r1) - 2 + rank_count()) % rank_count()))
      * rank_to_prime(rank((std::int32_t(r1) - 3 + rank_count()) % rank_count()))
      * rank_to_prime(rank((std::int32_t(r1) - 4 + rank_count()) % rank_count()));
    // if (!map.count(key)) Overwrite flushes.
      map[key] = hand_evaluation { hand_type::straight_flush, std::uint16_t(map.size()) };
  }

  return map;
}
inline std::unordered_map<std::int32_t, hand_evaluation> make_badugi_equivalence_classes            ()
{
  auto map = std::unordered_map<std::int32_t, hand_evaluation>();

  throw std::runtime_error("Equivalence class is not yet implemented!");

  return map;
}

inline std::unordered_map<std::int32_t, hand_evaluation> make_equivalence_classes                   (const ranking_type ranking_type = ranking_type::traditional)
{
  if (ranking_type == ranking_type::traditional)                                                                 return make_traditional_equivalence_classes       ();
  if (ranking_type == ranking_type::ace_to_five_low    || ranking_type == ranking_type::ace_to_five_high_low   ) return make_ace_to_five_low_equivalence_classes   ();
  if (ranking_type == ranking_type::ace_to_six_low     || ranking_type == ranking_type::ace_to_six_high_low    ) return make_ace_to_six_low_equivalence_classes    ();
  if (ranking_type == ranking_type::deuce_to_seven_low || ranking_type == ranking_type::deuce_to_seven_high_low) return make_deuce_to_seven_low_equivalence_classes();
  return make_badugi_equivalence_classes();
}
}

#endif
