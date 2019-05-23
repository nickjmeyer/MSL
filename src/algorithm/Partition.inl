#include <iterator>

#include <iostream>

namespace njm::algorithm
{

template <class Iterator, class UnaryPredicate>
constexpr Iterator partition(Iterator begin, Iterator end, UnaryPredicate predicate)
{
  while (begin != end)
  {
    while (begin != end && predicate(*begin))
    {
      ++begin;
    }
    while(begin != end && !predicate(*std::prev(end)))
    {
      --end;
    }
    if (begin != end && !predicate(*begin))
    {
      std::iter_swap(begin, std::prev(end));
    }
  }
  return begin;
}

}  // namespace njm::algorithm
