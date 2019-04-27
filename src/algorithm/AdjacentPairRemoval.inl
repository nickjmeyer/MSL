#include <cmath>

namespace njm::algorithm
{

template <class T>
decltype(auto) AbsDistRemoval::replace(const T& a, const T& b) const
{
  using DiffType = decltype(std::abs(std::declval<T>() - std::declval<T>()));
  return EvaluatedElement<T, DiffType>{(a + b) / 2, std::abs(a - b)};
}

template <class T, class Policy>
void remove_pairs_slow(std::vector<T>& elements, Policy policy, size_t target_size)
{
  for (size_t i = elements.size(); i > target_size; --i)
  {
    remove_one_pair(elements, policy);
  }
}

template <class T, class Policy>
void remove_one_pair(std::vector<T>& elements, Policy policy)
{
  if (elements.size() < 2)
  {
    return;
  }

  using EvaluatedElementType = decltype(std::declval<Policy>().replace(std::declval<T>(), std::declval<T>()));

  IndexedEvaluatedElement<typename std::vector<T>::iterator, EvaluatedElementType> best{std::begin(elements), policy.replace(elements[0], elements[1])};
  auto end = std::prev(std::end(elements));
  for (auto it = std::next(std::begin(elements)); it != end; ++it)
  {
    if (auto eval = policy.replace(*it, *std::next(it)); eval.cost < best.evaluation.cost)
    {
      best = {it, std::move(eval)};
    }
  }

  *best.index = best.evaluation.element;
  std::move(std::next(std::next(best.index)), std::end(elements), std::next(best.index));
  elements.pop_back();
}

}  // namespace njm::algorithm
