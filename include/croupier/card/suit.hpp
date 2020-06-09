#ifndef CROUPIER_CARD_SUIT_HPP
#define CROUPIER_CARD_SUIT_HPP

#include <cstddef>
#include <cstdint>

#include <magic_enum.hpp>

namespace cro
{
enum class suit : std::uint8_t
{
  clubs   ,
  diamonds,
  hearts  ,
  spades  
};

inline std::size_t suit_count    ()
{
  return magic_enum::enum_count<suit>();
}
inline char        suit_to_char  (const suit suit     )
{
  if (suit == suit::clubs   ) return 'c';
  if (suit == suit::diamonds) return 'd';
  if (suit == suit::hearts  ) return 'h';
  if (suit == suit::spades  ) return 's';
  return char(0);
}
inline suit        suit_from_char(const char character)
{
  if (character == 'c' || character == 'C') return suit::clubs   ;
  if (character == 'd' || character == 'D') return suit::diamonds;
  if (character == 'h' || character == 'H') return suit::hearts  ;
  if (character == 's' || character == 'S') return suit::spades  ;
  return suit(0);
}
}

#endif