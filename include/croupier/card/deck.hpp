#ifndef CROUPIER_CARD_DECK_HPP
#define CROUPIER_CARD_DECK_HPP

#include <deque>
#include <functional>
#include <random>
#include <vector>

#include <croupier/card/card.hpp>

namespace cro
{
class deck
{
public:
  deck           ()
  {
    for (std::size_t i = 0; i < rank_count() * suit_count(); ++i)
      cards_.emplace_back(i);
    shuffle();
  }
  deck           (const deck&  that) = default;
  deck           (      deck&& temp) = default;
 ~deck           ()                  = default;
  deck& operator=(const deck&  that) = default;
  deck& operator=(      deck&& temp) = default;

  // Moves the history_ into the back of the cards_.
  void                     reset  ()
  {
    cards_  .insert(cards_.end(), history_.begin(), history_.end());
    history_.clear ();
  }
  // Shuffles the cards_ according to a strategy (by default the Fisher-Yates shuffle).
  void                     shuffle(const std::function<void(std::deque<card>&)>& strategy = fisher_yates_shuffle)
  {
    strategy(cards_);
  }

  const card&              draw   ()
  {
    history_       .push_back(cards_.front());
    cards_         .pop_front();
    return history_.back     ();
  }
  [[nodiscard]]
  const card&              peek   () const
  {
    return cards_.front();
  }
  [[nodiscard]]
  std::size_t              size   () const
  {
    return cards_.size ();
  }
  [[nodiscard]]
  bool                     empty  () const
  {
    return cards_.empty();
  }

  [[nodiscard]]
  const std::deque <card>& cards  () const
  {
    return cards_;
  }
  [[nodiscard]]
  const std::vector<card>& history() const
  {
    return history_;
  }

protected:
  static void fisher_yates_shuffle(std::deque<card>& cards)
  {
    std::random_device                           random                    ;
    std::mt19937                                 mersenne_twister(random());
    std::uniform_int_distribution<std::uint16_t> distribution              ;
    for (auto i = cards.size() - 1; i > 0; --i)
    {
      distribution.param(std::uniform_int_distribution<std::uint16_t>::param_type(0, static_cast<std::uint16_t>(i)));
      std::swap(cards[i], cards[distribution(mersenne_twister)]);
    }
  }

  std::deque <card> cards_  ;
  std::vector<card> history_;
};
}

#endif