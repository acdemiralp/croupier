#ifndef CROUPIER_CARD_RANK_HPP
#define CROUPIER_CARD_RANK_HPP

#include <cstddef>
#include <cstdint>

#include <magic_enum.hpp>

namespace cro
{
enum class rank : std::uint8_t
{
  _2,
  _3,
  _4,
  _5,
  _6,
  _7,
  _8,
  _9,
  T ,
  J ,
  Q ,
  K ,
  A
};

inline std::size_t  rank_count     ()
{
  return magic_enum::enum_count<rank>();
}
inline char         rank_to_char   (const rank rank     )
{
  if (rank == rank::_2) return '2';
  if (rank == rank::_3) return '3';
  if (rank == rank::_4) return '4';
  if (rank == rank::_5) return '5';
  if (rank == rank::_6) return '6';
  if (rank == rank::_7) return '7';
  if (rank == rank::_8) return '8';
  if (rank == rank::_9) return '9';
  if (rank == rank::T ) return 'T';
  if (rank == rank::J ) return 'J';
  if (rank == rank::Q ) return 'Q';
  if (rank == rank::K ) return 'K';
  if (rank == rank::A ) return 'A';
  return static_cast<char>(0);
}
inline rank         rank_from_char (const char character)
{
  if (character == '2' )                    return rank::_2;
  if (character == '3' )                    return rank::_3;
  if (character == '4' )                    return rank::_4;
  if (character == '5' )                    return rank::_5;
  if (character == '6' )                    return rank::_6;
  if (character == '7' )                    return rank::_7;
  if (character == '8' )                    return rank::_8;
  if (character == '9' )                    return rank::_9;
  if (character == 'T' || character == 't') return rank::T ;
  if (character == 'J' || character == 'j') return rank::J ;
  if (character == 'Q' || character == 'q') return rank::Q ;
  if (character == 'K' || character == 'k') return rank::K ;
  if (character == 'A' || character == 'a') return rank::A ;
  return static_cast<rank>(0);
}

inline std::uint8_t rank_to_prime  (const rank rank     )
{
  if (rank == rank::_2) return 2 ;
  if (rank == rank::_3) return 3 ;
  if (rank == rank::_4) return 5 ;
  if (rank == rank::_5) return 7 ;
  if (rank == rank::_6) return 11;
  if (rank == rank::_7) return 13;
  if (rank == rank::_8) return 17;
  if (rank == rank::_9) return 19;
  if (rank == rank::T ) return 23;
  if (rank == rank::J ) return 29;
  if (rank == rank::Q ) return 31;
  if (rank == rank::K ) return 37;
  if (rank == rank::A ) return 41;
  return 0;
}
inline rank         rank_from_prime(const std::uint8_t prime)
{
  if (prime == 2 ) return rank::_2;
  if (prime == 3 ) return rank::_3;
  if (prime == 5 ) return rank::_4;
  if (prime == 7 ) return rank::_5;
  if (prime == 11) return rank::_6;
  if (prime == 13) return rank::_7;
  if (prime == 17) return rank::_8;
  if (prime == 19) return rank::_9;
  if (prime == 23) return rank::T ;
  if (prime == 29) return rank::J ;
  if (prime == 31) return rank::Q ;
  if (prime == 37) return rank::K ;
  if (prime == 41) return rank::A ;
  return static_cast<rank>(0);
}
}

#endif