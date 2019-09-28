#pragma once

namespace njm::algorithm
{

struct OptimisticPivot
{
  Iterator operator()(Iterator begin, Iterator target, Iterator end) const;
};

template <class Iterator, class PivotSelector>
void nth_element(Iterator begin, Iterator nth, Iterator end, PivotSelector pivot_selector);

}  // namespace njm::algorithm

#include "src/algorithm/NtElement.inl"
