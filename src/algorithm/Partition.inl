#include <iterator>

#include <iostream>

namespace njm::algorithm
{

template <class Iterator, class UnaryPredicate>
constexpr Iterator partition(Iterator begin, Iterator end, UnaryPredicate predicate)
{
  while (begin != end)
  {
    if (!predicate(*begin))
    {
      std::iter_swap(begin, std::prev(end));
      --end;
    }
    else
    {
      ++begin;
    }
  }
  return begin;
}

}  // namespace njm::algorithm
