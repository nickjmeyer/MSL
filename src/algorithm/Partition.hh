#pragma once

namespace njm::algorithm
{

/// @brief Partition the values between begin and end.
/// @param begin Start of the values to partition.
/// @param end One past the end of the values to partition.
/// @return An iterator to one past the last element such that the
/// predicate evaluates to true.
template <class Iterator, class UnaryPredicate>
constexpr Iterator partition(Iterator begin, Iterator end, UnaryPredicate predicate);


}  // namespace njm::algorithm

#include "src/algorithm/Partition.inl"
