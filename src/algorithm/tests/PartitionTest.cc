#include "src/algorithm/Partition.hh"
#include <gtest/gtest.h>

#include <array>

namespace njm::algorithm
{

TEST(Partition, Middle)
{
  std::array values{3, 5, 1, 3, 4, 2, 1, 7, 1, 5};
  auto predicate = [] (auto value)
                   {
                     return value < 4;
                   };

  auto middle = partition(std::begin(values), std::end(values), predicate);

  for (auto it = std::begin(values); it != middle; ++it)
  {
    ASSERT_TRUE(predicate(*it));
  }
  for (auto it = middle; it != std::end(values); ++it)
  {
    ASSERT_FALSE(predicate(*it));
  }
}

TEST(Partition, Begin)
{
  std::array values{3, 5, 1, 3, 4, 2, 1, 7, 1, 5};
  auto predicate = [] (auto value)
                   {
                     return value < 0;
                   };

  auto middle = partition(std::begin(values), std::end(values), predicate);

  ASSERT_TRUE(std::begin(values) == middle);

  for (auto it = std::begin(values); it != middle; ++it)
  {
    ASSERT_TRUE(predicate(*it));
  }
  for (auto it = middle; it != std::end(values); ++it)
  {
    ASSERT_FALSE(predicate(*it));
  }
}

TEST(Partition, End)
{
  std::array values{3, 5, 1, 3, 4, 2, 1, 7, 1, 5};
  auto predicate = [] (auto value)
                   {
                     return value > 0;
                   };

  auto middle = partition(std::begin(values), std::end(values), predicate);

  ASSERT_TRUE(std::end(values) == middle);

  for (auto it = std::begin(values); it != middle; ++it)
  {
    ASSERT_TRUE(predicate(*it));
  }
  for (auto it = middle; it != std::end(values); ++it)
  {
    ASSERT_FALSE(predicate(*it));
  }
}

}  // namespace njm::algorithm
