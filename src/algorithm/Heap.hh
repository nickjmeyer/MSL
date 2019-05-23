#pragma once

namespace njm::algorithm
{

namespace impl
{

template <class Iter, class Comp>
void heapifiy_one_position(Iter begin ,Iter end, Iter position, Comp comp);

} // namespace impl

template <class Iter, class Comp>
void make_heap(Iter begin, Iter end, Comp comp);

template <class Iter, class Comp>
void heapify(Iter begin, Iter end, Iter position, Comp comp);

template <class Iter, class Comp>
void pop_heap(Iter begin, Iter end, Comp comp);

template <class Iter, class Comp>
void push_heap(Iter begin, Iter end, Comp comp);

}  // namespace njm::algorithm

#include "src/algorithm/Heap.inl"
