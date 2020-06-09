#ifndef CROUPIER_CARD_CARD_HPP
#define CROUPIER_CARD_CARD_HPP

#include <cstdint>
#include <string>

#include <croupier/card/rank.hpp>
#include <croupier/card/suit.hpp>

namespace cro
{
class card
{
public:
  using index_type = std::uint8_t;
  
  explicit card   (const index_type index)           : index_(index)
  {
    
  }
  explicit card   (const rank rank, const suit suit) : card(index_type(rank) + index_type(suit) * rank_count())
  {
    
  }
  explicit card   (const std::string& string)        : card(rank_from_char(string[0]), suit_from_char(string[1]))
  {

  }
  card            (const card&  that) = default;
  card            (      card&& temp) = default;
 ~card            ()                  = default;
  card& operator= (const card&  that) = default;
  card& operator= (      card&& temp) = default;
  bool  operator==(const card&  that) const
  {
    return index_ == that.index_;
  }
  bool  operator< (const card&  that) const
  {
    if      (index_ % rank_count() == that.index_ % rank_count())
      return index_ / rank_count() <  that.index_ / rank_count();
    return   index_ % rank_count() <  that.index_ % rank_count();
  }

  index_type  index () const
  {
    return index_;
  }
  rank        rank  () const
  {
    return cro::rank(index_ % rank_count());
  }
  suit        suit  () const
  {
    return cro::suit(index_ / rank_count());
  }
  std::string string() const
  {
    return std::string(1, rank_to_char(rank())) + std::string(1, suit_to_char(suit()));
  }

protected:
  index_type index_ = 0;
};
}

#endif