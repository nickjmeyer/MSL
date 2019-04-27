#pragma once

#include <memory>
#include <vector>

namespace njm::algorithm
{

template <class T, class Cost>
struct EvaluatedElement
{
  T element;
  Cost cost;
};

template <class Index, class EvaluatedElementType>
struct IndexedEvaluatedElement
{
  Index index;
  EvaluatedElementType evaluation;
};

struct AbsDistRemoval
{
  template <class T>
  decltype(auto) replace(const T& a, const T& b) const;
};

template <class T, class Policy>
void remove_pairs_slow(std::vector<T>& elements, Policy policy, size_t target_size);

template <class T, class Policy>
void remove_one_pair(std::vector<T>& elements, Policy policy);

}  // namespace njm::algorithm

#include "src/algorithm/AdjacentPairRemoval.inl"
