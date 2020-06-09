#ifndef CROUPIER_CARD_CARD_SET_HPP
#define CROUPIER_CARD_CARD_SET_HPP

#include <algorithm>
#include <bitset>
#include <cstddef>
#include <string>
#include <vector>

#include <croupier/card/card.hpp>
#include <croupier/utility/intrinsics.hpp>

namespace cro
{
class card_set
{
public:
  using bitset_type = std::bitset<52>;
  
  explicit card_set   (const bitset_type        bitset = bitset_type()) : bitset_(bitset)
  {
    
  }
  explicit card_set   (const card               card  )
  {
    insert(card);
  }
  explicit card_set   (const std::vector<card>& cards )
  {
    for (auto& card : cards)
      insert(card);
  }
  explicit card_set   (const std::string&       string)
  {
    for (std::size_t i = 0; i < string.size(); i += 2)
      insert(card(string.substr(2 * i, 2)));
  }
  card_set            (const card_set&  that) = default;
  card_set            (      card_set&& temp) = default;
 ~card_set            ()                      = default;
  card_set& operator= (const card_set&  that) = default;
  card_set& operator= (      card_set&& temp) = default;

  card_set  operator&  (const card_set&   that ) const
  {
    return card_set(bitset_ & that.bitset_);
  }
  card_set  operator|  (const card_set&   that ) const
  {
    return card_set(bitset_ | that.bitset_);
  }
  card_set  operator^  (const card_set&   that ) const
  {
    return card_set(bitset_ ^ that.bitset_);
  }
  card_set& operator&= (const card_set&   that )
  {
    bitset_ &= that.bitset_;
    return *this;
  }
  card_set& operator|= (const card_set&   that )
  {
    bitset_ |= that.bitset_;
    return *this;
  }
  card_set& operator^= (const card_set&   that )
  {
    bitset_ ^= that.bitset_;
    return *this;
  }
  card_set  operator~  () const
  {
    return card_set(~bitset_);
  }
  bool      operator== (const card_set&   that ) const
  {
    return bitset_ == that.bitset_;
  }
  bool      operator!= (const card_set&   that ) const
  {
    return bitset_ != that.bitset_;
  }
  bool      operator<  (const card_set&   that ) const
  {
    return bitset_.to_ullong() < that.bitset_.to_ullong();
  }
  bool      operator>  (const card_set&   that ) const
  {
    return bitset_.to_ullong() > that.bitset_.to_ullong();
  }
  card_set  operator<< (const std::size_t shift) const
  {
    return card_set(bitset_ << shift);
  }
  card_set  operator>> (const std::size_t shift) const
  {
    return card_set(bitset_ >> shift);
  }
  card_set& operator<<=(const std::size_t shift)
  {
    bitset_ <<= shift;
    return *this;
  }
  card_set& operator>>=(const std::size_t shift)
  {
    bitset_ >>= shift;
    return *this;
  }

  std::size_t           count          () const
  {
    return bitset_.count();
  }
  std::size_t           size           () const
  {
    return bitset_.size ();
  }
  void                  set            ()
  {
    bitset_.set  ();
  }
  void                  reset          ()
  {
    bitset_.reset();
  }
                                       
  std::string           string         () const
  {
    std::string string;

    auto bitset = bitset_.to_ullong();
    while (bitset)
    {
      string += card(lsb(bitset)).string();
      pop_lsb(bitset);
    }

    return string;
  }
                                       
  void                  insert         (const card_set& that)
  {
    *this |= that;
  }
  void                  insert         (const card&     card)
  {
    bitset_ |= (bitset_type(1) << card.index());
  }
  void                  erase          (const card_set& that)
  {
    *this ^= that;
  }
  void                  erase          (const card&     card)
  {
    bitset_ ^= (bitset_type(1) << card.index());
  }
  bool                  contains       (const card_set& that) const
  {
    return (*this & that) == that;
  }
  bool                  contains       (const card&     card) const
  {
    return (bitset_ & (bitset_type(1) << card.index())) != 0;
  }
  bool                  intersects     (const card_set& that) const
  {
    return (*this & that) != card_set(bitset_type(0));
  }
  bool                  disjoint       (const card_set& that) const
  {
    return (*this & that) == card_set(bitset_type(0));
  }
                                       
  std::vector<card>     cards          () const
  {
    std::vector<card> cards;

    auto bitset = bitset_.to_ullong();
    while (bitset)
    {
      cards.emplace_back(lsb(bitset));
      pop_lsb(bitset);
    }

    return cards;
  }
  std::vector<card_set> split          () const
  {
    std::vector<card_set> cardsets;

    auto bitset = bitset_.to_ullong();
    while (bitset)
    {
      cardsets.emplace_back(card(lsb(bitset)));
      pop_lsb(bitset);
    }

    return cardsets;
  }
                                       
  std::vector<card_set> combinations   (const std::size_t k) const
  {
    auto combinations = std::vector<card_set>();
    auto selector     = std::vector<bool>(bitset_.count());
    auto split_cards  = cards();
    std::fill(selector.begin(), selector.begin() + k, true);
    do
    {
      auto& combination = combinations.emplace_back();
      for (std::size_t i = 0; i < selector.size(); ++i)
        if (selector[i])
          combination.insert(card(split_cards[i]));
    } while (std::prev_permutation(selector.begin(), selector.end()));
    return combinations;
  }

  bitset_type           bitset         () const
  {
    return bitset_;
  }

protected:
  bitset_type bitset_;
};

inline std::vector<card_set> operator&(const std::vector<card_set>& lhs, const std::vector<card_set>& rhs)
{
  std::vector<card_set> result(lhs.size() * rhs.size());
  for (std::size_t l = 0; l < lhs.size(); ++l)
    for (std::size_t r = 0; r < rhs.size(); ++r)
      result[l * rhs.size() + r] = lhs[l] & rhs[r];
  return result;
}
inline std::vector<card_set> operator|(const std::vector<card_set>& lhs, const std::vector<card_set>& rhs)
{
  std::vector<card_set> result(lhs.size() * rhs.size());
  for (std::size_t l = 0; l < lhs.size(); ++l)
    for (std::size_t r = 0; r < rhs.size(); ++r)
      result[l * rhs.size() + r] = lhs[l] | rhs[r];
  return result;
}
inline std::vector<card_set> operator^(const std::vector<card_set>& lhs, const std::vector<card_set>& rhs)
{
  std::vector<card_set> result(lhs.size() * rhs.size());
  for (std::size_t l = 0; l < lhs.size(); ++l)
    for (std::size_t r = 0; r < rhs.size(); ++r)
      result[l * rhs.size() + r] = lhs[l] ^ rhs[r];
  return result;
}
}

#endif