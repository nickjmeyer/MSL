#include <iterator>

#include <iostream>

namespace njm::algorithm
{

template <class Iterator, class UnaryPredicate>
constexpr Iterator partition(Iterator begin, Iterator end, UnaryPredicate predicate)
{
  if (begin == end)
  {
    return begin;
  }

  while (predicate(*begin))
  {
    ++begin;
    if (begin == end)
    {
      return begin;
    }
  }

  if (begin == std::prev(end))
  {
    return begin;
  }

  while (!predicate(*std::prev(end)))
  {
    --end;
  }

  if (begin == end)
  {
    return begin;
  }

  std::iter_swap(begin, std::prev(end));

  while (true)
  {
    do
    {
      ++begin;
    } while (predicate(*begin));

    if (begin == std::prev(end))
    {
      return begin;
    }

    do {
      --end;
    } while (!predicate(*std::prev(end)));

    if (begin == end)
    {
      return begin;
    }

    std::iter_swap(begin, std::prev(end));
  }
}

}  // namespace njm::algorithm
