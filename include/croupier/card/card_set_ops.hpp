#ifndef CROUPIER_CARD_CARD_SET_OPS_HPP
#define CROUPIER_CARD_CARD_SET_OPS_HPP

#include <bitset>
#include <vector>

#include <croupier/card/card_set.hpp>

namespace cro
{
inline std::vector<card_set>        make_rank_masks    ()
{
  std::vector<card_set> rank_masks(rank_count());
  card_set              rank_mask (card_set::bitset_type("1000000000000100000000000010000000000001000000000000")); // Start at 2s (end at As).
  for (auto& iteratee : rank_masks)
  {
    iteratee = rank_mask;
    rank_mask >>= 1;
  }
  return rank_masks;
}
inline std::vector<card_set>        make_suit_masks    ()
{
  std::vector<card_set> suit_masks(rank_count());
  card_set              suit_mask (card_set::bitset_type("1111111111111000000000000000000000000000000000000000")); // Start at clubs (end at spades).
  for (auto& iteratee : suit_masks)
  {
    iteratee = suit_mask;
    suit_mask >>= 13;
  }
  return suit_masks;
}
inline std::vector<std::bitset<13>> make_straight_masks()
{
  std::vector     straight_masks(10, std::bitset<13>("1111000000001")); // A2345 is a special case.
  std::bitset<13> straight_mask ("1111100000000"); // Start at 23456 (end at TJQKA).
  for (std::size_t i = 1; i < straight_masks.size(); ++i)
  {
    straight_masks[i] = straight_mask;
    straight_mask >>= 1;
  }
  return straight_masks;
}

inline std::vector<card_set>        rank_masks     = make_rank_masks    ();
inline std::vector<card_set>        suit_masks     = make_suit_masks    ();
inline std::vector<std::bitset<13>> straight_masks = make_straight_masks();
}

#endif