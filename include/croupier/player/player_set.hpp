#ifndef CROUPIER_PLAYER_PLAYER_SET_HPP
#define CROUPIER_PLAYER_PLAYER_SET_HPP

#include <bit>
#include <cstddef>
#include <string>

#include <boost/dynamic_bitset.hpp>

#include <croupier/player/player.hpp>

namespace cro
{
class player_set
{
public:
  using bitset_type = boost::dynamic_bitset<>;

  explicit player_set              (const bitset_type bitset = bitset_type()) : bitset_(bitset)
  {
    
  }
  explicit player_set              (const std::size_t size) : bitset_(size)
  {

  }
  explicit player_set              (const player& player);
  player_set                       (const player_set&  that) = default;
  player_set                       (      player_set&& temp) = default;
 ~player_set                       ()                        = default;
  player_set&            operator= (const player_set&  that) = default;
  player_set&            operator= (      player_set&& temp) = default;

  bool                   operator==(const player_set&  that) const
  {
    return bitset_ == that.bitset_;
  }
  bool                   operator!=(const player_set&  that) const
  {
    return bitset_ != that.bitset_;
  }
  bool                   operator[](const std::size_t  position) const
  {
    return bitset_[position];
  }
  bitset_type::reference operator[](const std::size_t  position)
  {
    return bitset_[position];
  }

  std::size_t count             () const
  {
    return bitset_.count();
  }
  std::size_t size              () const
  {
    return bitset_.size ();
  }
  void        resize            (const std::size_t size)
  {
    bitset_.resize(size);
  }
  void        set               ()
  {
    bitset_.set  ();
  }
  void        reset             ()
  {
    bitset_.reset();
  }

  std::string string            () const
  {
    std::string string;
    to_string(bitset_, string);
    return      string;
  }

  void        rotate_left       (const std::size_t count = 1)
  {
    bitset_ = bitset_ << count | bitset_ >> (bitset_.size() - count);
  }
  void        rotate_right      (const std::size_t count = 1)
  {
    bitset_ = bitset_ >> count | bitset_ << (bitset_.size() - count);
  }

  std::size_t find_first        () const
  {
    return bitset_.find_first();
  }
  std::size_t find_next         (const std::size_t index) const
  {
    return bitset_.find_next(index);
  }
  void        iterate           (const std::function<void(std::size_t)>& callback) const
  {
    auto index = find_first();
    if (index != bitset_type::npos)
      callback(index);

    while (index != bitset_type::npos)
    {
      index = find_next(index);
      if (index != bitset_type::npos)
        callback(index);
    }
  }

  std::size_t find_next_circular(const std::size_t index) const
  {
    const auto next_index = find_next(index);
    return next_index != bitset_type::npos ? next_index : find_first();
  }
  void        iterate_circular  (const std::size_t start, const std::function<void(std::size_t)>& callback) const
  {
    if (bitset_[start])
      callback(start);

    auto index = find_next_circular(start);
    while (index != start)
    {
      callback(index);
      index = find_next_circular(index);
    }
  }

  bitset_type bitset            () const
  {
    return bitset_;
  }

protected:
  bitset_type bitset_;
};
}

#endif