#include <Heap.hh>
#include <gtest/gtest.h>

#include <array>

namespace njm::algorithm
{

TEST(Heap, Testing)
{

  std::array values {1, 2, 3};

  make_heap(std::begin(values), std::end(values), std::less{});

}

}  // namespace njm::algorithm
