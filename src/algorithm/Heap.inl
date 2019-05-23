#include <iterator>

namespace njm::algorithm
{

namespace impl
{

template <class Iter, class Comp>
Iter heapify_one_position(Iter begin, Iter end, Iter position, Comp comp)
{
  auto n = 2 * std::distance(begin, position) + 1;
  auto s = std::distance(begin, end);

  if (n >= s)
  {
    return position;
  }

  auto left = begin + n;
  if (n + 1 >= s)
  {
    if (comp(*left, *position))
    {
      std::iter_swap(left, position);
      return left;
    }
    return position;
  }

  auto right = std::next(left);
  auto cand = comp(*left, *right) ? left : right;

  if (comp(*cand, *position))
  {
    std::iter_swap(cand, position);
    return cand;
  }

  return position;
}

}  // namespace impl

template <class Iter, class Comp>
void heapify(Iter begin, Iter end, Iter position, Comp comp)
{
  Iter next_position{};
  do
  {
    next_position = position;
    position = impl::heapify_one_position(begin, end, next_position, comp);
  } while(next_position != position);
}

template <class Iter, class Comp>
void make_heap(Iter begin, Iter end, Comp comp)
{
  Iter position{end};
  while(position != begin)
  {
    --position;
    heapify(begin, end, position, comp);
  }
}

template <class Iter, class Comp>
void pop_heap(Iter begin, Iter end, Comp comp)
{
  auto n = std::distance(begin, end);
  if (n <= 1)
  {
    return;
  }

  --end;
  std::iter_swap(begin, end);
  heapify(begin, begin, end, comp);
}

template <class Iter, class Comp>
void push_heap(Iter begin, Iter end, Comp comp)
{
  Iter position{end};
  while (position != begin)
  {
    --position;
    auto n = (std::distance(begin, position) - 1) / 2;
    position = begin + n;
    heapify(begin, end, position, comp);
  }
}

} // namespace njm::algorithm
