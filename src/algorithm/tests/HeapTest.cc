#include "src/algorithm/Heap.hh"
#include <gtest/gtest.h>

#include <algorithm>
#include <array>

namespace na = njm::algorithm;

TEST(Heapify, Empty)
{
  std::array<int32_t, 0> values{};

  na::heapify(std::begin(values), std::end(values), std::end(values), std::less{});
}

TEST(Heapify, One_Element)
{
  std::array values{1};

  na::heapify(std::begin(values), std::end(values), std::begin(values), std::less{});

  std::array ground_truth{1};

  ASSERT_TRUE(std::equal(std::begin(values), std::end(values),
                         std::begin(ground_truth), std::end(ground_truth)));
}

TEST(Heapify, Two_Elements)
{
  std::array values{2, 1};

  na::heapify(std::begin(values), std::end(values), std::begin(values), std::less{});

  std::array ground_truth{1, 2};

  ASSERT_TRUE(std::equal(std::begin(values), std::end(values),
                         std::begin(ground_truth), std::end(ground_truth)));
}

TEST(Heapify, Three_Elements)
{
  std::array values{3, 2, 1};

  na::heapify(std::begin(values), std::end(values), std::begin(values), std::less{});

  std::array ground_truth{1, 2, 3};

  ASSERT_TRUE(std::equal(std::begin(values), std::end(values),
                         std::begin(ground_truth), std::end(ground_truth)));

  values = {3, 1, 2};

  na::heapify(std::begin(values), std::end(values), std::begin(values), std::less{});

  ground_truth = {1, 3, 2};

  ASSERT_TRUE(std::equal(std::begin(values), std::end(values),
                         std::begin(ground_truth), std::end(ground_truth)));
}

TEST(Heapify, Seven_Elements)
{
  std::array values{7, 6, 5, 4, 3, 2, 1};

  std::array ground_truth{5, 6, 1, 4, 3, 2, 7};

  na::heapify(std::begin(values), std::end(values), std::begin(values), std::less{});

  ASSERT_TRUE(std::equal(std::begin(values), std::end(values),
                         std::begin(ground_truth), std::end(ground_truth)));

}

TEST(MakeHeap, Seven_Elements)
{
  std::array values{7, 6, 5, 4, 3, 2, 1};

  na::make_heap(std::begin(values), std::end(values), std::less{});

  std::cout << *std::begin(values);
  for (auto it = std::next(std::begin(values)); it != std::end(values); ++it)
  {
    std::cout << ", " << *it;
  }
  std::cout << "\n";

  ASSERT_TRUE(std::is_heap(std::begin(values), std::end(values), std::greater{}));
}
