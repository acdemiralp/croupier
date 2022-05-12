#ifndef CROUPIER_UTILITY_INTRINSICS_HPP
#define CROUPIER_UTILITY_INTRINSICS_HPP

#include <cstdint>

#if defined(_MSC_VER)
#include <intrin.h>
#endif

namespace cro
{
#if defined(__GNUC__) // GCC, Clang, ICC
inline std::uint8_t lsb     (const std::uint64_t  bitset)
{
  return static_cast<std::uint8_t>(     __builtin_ctzll(bitset));
}
inline std::uint8_t msb     (const std::uint64_t  bitset)
{
  return static_cast<std::uint8_t>(63 ^ __builtin_clzll(bitset));
}
#elif defined(_MSC_VER) // MSVC
inline std::uint8_t lsb     (const std::uint64_t  bitset)
{
  unsigned long index;
  _BitScanForward64(&index, bitset);
  return static_cast<std::uint8_t>(index);
}
inline std::uint8_t msb     (const std::uint64_t  bitset)
{
  unsigned long index;
  _BitScanReverse64(&index, bitset);
  return static_cast<std::uint8_t>(index);
}
#else  // Compiler is neither GCC nor MSVC
#error "Compiler not supported."
#endif

inline void         pop_lsb (      std::uint64_t& bitset)
{
  bitset &= (bitset - 1);
}
}

#endif
