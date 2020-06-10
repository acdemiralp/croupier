#ifndef CROUPIER_EVALUATOR_EQUIVALENCE_CLASSES_TRADITIONAL_EQUIVALENCE_CLASSES_HPP
#define CROUPIER_EVALUATOR_EQUIVALENCE_CLASSES_TRADITIONAL_EQUIVALENCE_CLASSES_HPP

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
inline std::unordered_map<std::int32_t, hand_evaluation> make_equivalence_classes<ranking_type::traditional, 1>()
{
  auto map   = std::unordered_map<std::int32_t, hand_evaluation>();
  auto ranks = std::vector<rank>
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

  // Generate high-cards.
  for (auto& r1 : ranks)
  {
    const auto key = rank_to_prime(r1);
    if (!map.count(key))
      map[key] = hand_evaluation { hand_type::high_card, std::uint16_t(map.size()) };
  }

  return map;
}
template <>
inline std::unordered_map<std::int32_t, hand_evaluation> make_equivalence_classes<ranking_type::traditional, 2>()
{
  auto map   = std::unordered_map<std::int32_t, hand_evaluation>();
  auto ranks = std::vector<rank>
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

  // Generate pairs.
  for (auto& r1 : ranks)
  {
    const auto key = std::pow(rank_to_prime(r1), 2);
    if (!map.count(key))
      map[key] = hand_evaluation { hand_type::pair, std::uint16_t(map.size()) };
  }

  // Generate high-cards.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;
      const auto key = rank_to_prime(r1) * rank_to_prime(r2);
      if (!map.count(key))
        map[key] = hand_evaluation { hand_type::high_card, std::uint16_t(map.size()) };
    }
  }

  return map;
}
template <>
inline std::unordered_map<std::int32_t, hand_evaluation> make_equivalence_classes<ranking_type::traditional, 3>()
{
  auto map   = std::unordered_map<std::int32_t, hand_evaluation>();
  auto ranks = std::vector<rank>
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

  // Generate three-of-a-kinds.
  for (auto& r1 : ranks)
  {
    const auto key = std::pow(rank_to_prime(r1), 3);
    if (!map.count(key))
      map[key] = hand_evaluation { hand_type::three_of_a_kind, std::uint16_t(map.size()) };
  }
 
  // Generate pairs.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;

      const auto key = std::pow(rank_to_prime(r1), 2) * rank_to_prime(r2);
      if (!map.count(key))
        map[key] = hand_evaluation { hand_type::pair, std::uint16_t(map.size()) };
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

        const auto key = rank_to_prime(r1) * rank_to_prime(r2) * rank_to_prime(r3);
        if (!map.count(key))
          map[key] = hand_evaluation { hand_type::high_card, std::uint16_t(map.size()) };
      }
    }
  }

  return map;
}
template <>
inline std::unordered_map<std::int32_t, hand_evaluation> make_equivalence_classes<ranking_type::traditional, 4>()
{
  auto map   = std::unordered_map<std::int32_t, hand_evaluation>();
  auto ranks = std::vector<rank>
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

  // Generate four-of-a-kinds.
  for (auto& r1 : ranks)
  {
    const auto key = std::pow(rank_to_prime(r1), 4);
    if (!map.count(key))
      map[key] = hand_evaluation { hand_type::four_of_a_kind, std::uint16_t(map.size()) };
  }

  // Generate three-of-a-kinds.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;

      const auto key = std::pow(rank_to_prime(r1), 3) * rank_to_prime(r2);
      if (!map.count(key))
        map[key] = hand_evaluation { hand_type::three_of_a_kind, std::uint16_t(map.size()) };
    }
  }

  // Generate two pairs.
  for (auto& r1 : ranks)
  {
    for (auto& r2 : ranks)
    {
      if (r1 == r2) continue;
      
      const auto key = std::pow(rank_to_prime(r1), 2) * std::pow(rank_to_prime(r2), 2);
      if (!map.count(key))
        map[key] = hand_evaluation { hand_type::two_pairs, std::uint16_t(map.size()) };
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

        const auto key = std::pow(rank_to_prime(r1), 2) * rank_to_prime(r2) * rank_to_prime(r3);
        if (!map.count(key))
          map[key] = hand_evaluation { hand_type::pair, std::uint16_t(map.size()) };
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
          
          const auto key = rank_to_prime(r1) * rank_to_prime(r2) * rank_to_prime(r3) * rank_to_prime(r4);
          if (!map.count(key))
            map[key] = hand_evaluation { hand_type::high_card, std::uint16_t(map.size()) };
        }
      }
    }
  }

  return map;
}
template <>
inline std::unordered_map<std::int32_t, hand_evaluation> make_equivalence_classes<ranking_type::traditional, 5>()
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
}

#endif