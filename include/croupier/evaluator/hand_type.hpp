#ifndef CROUPIER_EVALUATOR_HAND_TYPE_HPP
#define CROUPIER_EVALUATOR_HAND_TYPE_HPP

#include <cstdint>
#include <string>

namespace cro
{
enum class hand_type : std::uint8_t
{
  high_card      ,
  pair           ,
  two_pairs      ,
  three_of_a_kind,
  straight       ,
  flush          ,
  full_house     ,
  four_of_a_kind ,
  straight_flush  
};

inline std::string hand_type_to_string  (const hand_type    hand_type)
{
  if (hand_type == hand_type::high_card       ) return "HC";
  if (hand_type == hand_type::pair            ) return "1P";
  if (hand_type == hand_type::two_pairs       ) return "2P";
  if (hand_type == hand_type::three_of_a_kind ) return "3K";
  if (hand_type == hand_type::straight        ) return "ST";
  if (hand_type == hand_type::flush           ) return "FL";
  if (hand_type == hand_type::full_house      ) return "FH";
  if (hand_type == hand_type::four_of_a_kind  ) return "4K";
  if (hand_type == hand_type::straight_flush  ) return "SF";
  return {};
}
inline hand_type   hand_type_from_string(const std::string& string   )
{
  if (string == "HC") return hand_type::high_card      ;
  if (string == "1P") return hand_type::pair           ;
  if (string == "2P") return hand_type::two_pairs      ;
  if (string == "3K") return hand_type::three_of_a_kind;
  if (string == "ST") return hand_type::straight       ;
  if (string == "FL") return hand_type::flush          ;
  if (string == "FH") return hand_type::full_house     ;
  if (string == "4K") return hand_type::four_of_a_kind ;
  if (string == "SF") return hand_type::straight_flush ;
  return static_cast<hand_type>(0);
}
}

#endif