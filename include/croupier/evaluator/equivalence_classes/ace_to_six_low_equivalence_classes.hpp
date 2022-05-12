#ifndef CROUPIER_EVALUATOR_EQUIVALENCE_CLASSES_ACE_TO_SIX_LOW_EQUIVALENCE_CLASSES_HPP
#define CROUPIER_EVALUATOR_EQUIVALENCE_CLASSES_ACE_TO_SIX_LOW_EQUIVALENCE_CLASSES_HPP

#include <cmath>
#include <cstdint>
#include <unordered_map>
#include <vector>

#include <croupier/card/rank.hpp>
#include <croupier/evaluator/equivalence_class.hpp>
#include <croupier/evaluator/hand_evaluation.hpp>
#include <croupier/ruleset/ranking_type.hpp>

namespace cro
{
template <>
inline std::unordered_map<std::int32_t, hand_evaluation> make_equivalence_classes<ranking_type::ace_to_six_low, 1>()
{
  auto       map   = std::unordered_map<std::int32_t, hand_evaluation>();
  const auto ranks = std::vector
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
    if (const auto key = rank_to_prime(r1) * rank_to_prime(r1); !map.count(key))
      map[key] = hand_evaluation{ hand_type::high_card, static_cast<std::uint16_t>(map.size()) };
  }

  return map;
}
template <>
inline std::unordered_map<std::int32_t, hand_evaluation> make_equivalence_classes<ranking_type::ace_to_six_low, 2>()
{
  auto       map   = std::unordered_map<std::int32_t, hand_evaluation>();
  const auto ranks = std::vector
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

      if (const auto key = rank_to_prime(r1) * rank_to_prime(r2); !map.count(key))
        map[key] = hand_evaluation{ hand_type::high_card, static_cast<std::uint16_t>(map.size()) };
    }
  }

  // Generate pairs.
  for (auto& r1 : ranks)
  {
    if (const auto key = static_cast<std::int32_t>(std::pow(rank_to_prime(r1), 2)); !map.count(key))
      map[key] = hand_evaluation{ hand_type::pair, static_cast<std::uint16_t>(map.size()) };
  }

  return map;
}
template <>
inline std::unordered_map<std::int32_t, hand_evaluation> make_equivalence_classes<ranking_type::ace_to_six_low, 3>()
{
  auto       map   = std::unordered_map<std::int32_t, hand_evaluation>();
  const auto ranks = std::vector
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

        if (const auto key = rank_to_prime(r1) * rank_to_prime(r2) * rank_to_prime(r3); !map.count(key))
          map[key] = hand_evaluation{ hand_type::high_card, static_cast<std::uint16_t>(map.size()) };
      }
    }
  }

  // Generate pairs.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;

      if (const auto key = static_cast<std::int32_t>(std::pow(rank_to_prime(r1), 2)) * rank_to_prime(r2); !map.count(key))
        map[key] = hand_evaluation { hand_type::pair, static_cast<std::uint16_t>(map.size()) };
    }
  }

  // Generate three-of-a-kinds.
  for (auto& r1 : ranks)
  {
    if (const auto key = static_cast<std::int32_t>(std::pow(rank_to_prime(r1), 3)); !map.count(key))
      map[key] = hand_evaluation{ hand_type::three_of_a_kind, static_cast<std::uint16_t>(map.size()) };
  }

  return map;
}
template <>
inline std::unordered_map<std::int32_t, hand_evaluation> make_equivalence_classes<ranking_type::ace_to_six_low, 4>()
{
  auto       map   = std::unordered_map<std::int32_t, hand_evaluation>();
  const auto ranks = std::vector
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

          if (const auto key = rank_to_prime(r1) * rank_to_prime(r2) * rank_to_prime(r3) * rank_to_prime(r4); !map.count(key))
            map[key] = hand_evaluation { hand_type::high_card, static_cast<std::uint16_t>(map.size()) };
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

        if (const auto key = static_cast<std::int32_t>(std::pow(rank_to_prime(r1), 2)) * rank_to_prime(r2) * rank_to_prime(r3); !map.count(key))
          map[key] = hand_evaluation { hand_type::pair, static_cast<std::uint16_t>(map.size()) };
      }
    }
  }

  // Generate two pairs.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;

      if (const auto key = static_cast<std::int32_t>(std::pow(rank_to_prime(r1), 2) * std::pow(rank_to_prime(r2), 2)); !map.count(key))
        map[key] = hand_evaluation{ hand_type::two_pairs, static_cast<std::uint16_t>(map.size()) };
    }
  }

  // Generate three-of-a-kinds.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;

      if (const auto key = static_cast<std::int32_t>(std::pow(rank_to_prime(r1), 3)) * rank_to_prime(r2); !map.count(key))
        map[key] = hand_evaluation { hand_type::three_of_a_kind, static_cast<std::uint16_t>(map.size()) };
    }
  }

  // Generate four-of-a-kinds.
  for (auto& r1 : ranks)
  {
    if (const auto key = static_cast<std::int32_t>(std::pow(rank_to_prime(r1), 4)); !map.count(key))
      map[key] = hand_evaluation{ hand_type::four_of_a_kind, static_cast<std::uint16_t>(map.size()) };
  }

  return map;
}
template <>
inline std::unordered_map<std::int32_t, hand_evaluation> make_equivalence_classes<ranking_type::ace_to_six_low, 5>()
{
  auto       map       = std::unordered_map<std::int32_t, hand_evaluation>();
  const auto ranks     = std::vector
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
  auto straights = std::vector
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

            if (const auto key = rank_to_prime(r1) * rank_to_prime(r2) * rank_to_prime(r3) * rank_to_prime(r4) * rank_to_prime(r5); !map.count(key))
              map[key] = hand_evaluation { hand_type::high_card, static_cast<std::uint16_t>(map.size()) };
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

          if (const auto key = static_cast<std::int32_t>(std::pow(rank_to_prime(r1), 2)) * rank_to_prime(r2) * rank_to_prime(r3) * rank_to_prime(r4); !map.count(key))
            map[key] = hand_evaluation { hand_type::pair, static_cast<std::uint16_t>(map.size()) };
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

        if (const auto key = static_cast<std::int32_t>(std::pow(rank_to_prime(r1), 2) * std::pow(rank_to_prime(r2), 2)) * rank_to_prime(r3); !map.count(key))
          map[key] = hand_evaluation { hand_type::two_pairs, static_cast<std::uint16_t>(map.size()) };
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

        if (const auto key = static_cast<std::int32_t>(std::pow(rank_to_prime(r1), 3)) * rank_to_prime(r2) * rank_to_prime(r3); !map.count(key))
          map[key] = hand_evaluation { hand_type::three_of_a_kind, static_cast<std::uint16_t>(map.size()) };
      }
    }
  }

  // Generate straights.
  for (auto& r1 : straights)
  {
    const auto key = 
        rank_to_prime(r1)
      * rank_to_prime(static_cast<rank>((static_cast<std::int32_t>(r1) - 1 + rank_count()) % rank_count()))
      * rank_to_prime(static_cast<rank>((static_cast<std::int32_t>(r1) - 2 + rank_count()) % rank_count()))
      * rank_to_prime(static_cast<rank>((static_cast<std::int32_t>(r1) - 3 + rank_count()) % rank_count()))
      * rank_to_prime(static_cast<rank>((static_cast<std::int32_t>(r1) - 4 + rank_count()) % rank_count()));
    // if (!map.count(key)) Overwrite high cards.
      map[key] = hand_evaluation { hand_type::straight, static_cast<std::uint16_t>(map.size()) };
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

            if (const auto key = - rank_to_prime(r1) * rank_to_prime(r2) * rank_to_prime(r3) * rank_to_prime(r4) * rank_to_prime(r5); !map.count(key))
              map[key] = hand_evaluation { hand_type::flush, static_cast<std::uint16_t>(map.size()) };
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

      if (const auto key = static_cast<std::int32_t>(std::pow(rank_to_prime(r1), 3) * std::pow(rank_to_prime(r2), 2)); !map.count(key))
        map[key] = hand_evaluation { hand_type::full_house, static_cast<std::uint16_t>(map.size()) };
    }
  }

  // Generate four-of-a-kinds.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;

      if (const auto key = static_cast<std::int32_t>(std::pow(rank_to_prime(r1), 4)) * rank_to_prime(r2); !map.count(key))
        map[key] = hand_evaluation { hand_type::four_of_a_kind, static_cast<std::uint16_t>(map.size()) };
    }
  }

  // Generate straight flushes.
  for (auto& r1 : straights)
  {
    const auto key = 
      - rank_to_prime(r1)
      * rank_to_prime(static_cast<rank>((static_cast<std::int32_t>(r1) - 1 + rank_count()) % rank_count()))
      * rank_to_prime(static_cast<rank>((static_cast<std::int32_t>(r1) - 2 + rank_count()) % rank_count()))
      * rank_to_prime(static_cast<rank>((static_cast<std::int32_t>(r1) - 3 + rank_count()) % rank_count()))
      * rank_to_prime(static_cast<rank>((static_cast<std::int32_t>(r1) - 4 + rank_count()) % rank_count()));
    // if (!map.count(key)) Overwrite flushes.
      map[key] = hand_evaluation { hand_type::straight_flush, static_cast<std::uint16_t>(map.size()) };
  }

  return map;
}
}

#endif