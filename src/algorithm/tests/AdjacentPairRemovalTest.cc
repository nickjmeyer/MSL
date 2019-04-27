#include "src/algorithm/AdjacentPairRemoval.hh"
#include <gtest/gtest.h>

#include <iostream>

namespace njm::algorithm
{

TEST(AdjacenyPairRemoval, Slow_AlwaysFirstPair)
{
  const std::vector<int32_t> original_values{1, 3, 5, 8};
  std::vector<int32_t> one_by_one{original_values};
  {
    const std::vector<int32_t> truth{2, 5, 8};
    std::vector<int32_t> original_copy{original_values};
    remove_pairs_slow(original_copy, AbsDistRemoval{}, truth.size());
    remove_one_pair(one_by_one, AbsDistRemoval{});

    ASSERT_TRUE(std::equal(std::begin(one_by_one),
                           std::end(one_by_one),
                           std::begin(truth),
                           std::end(truth)));

    ASSERT_TRUE(std::equal(std::begin(original_copy),
                           std::end(original_copy),
                           std::begin(truth),
                           std::end(truth)));
  }

  {
    std::vector<int32_t> truth{3, 8};
    std::vector<int32_t> original_copy{original_values};
    remove_pairs_slow(original_copy, AbsDistRemoval{}, truth.size());
    remove_one_pair(one_by_one, AbsDistRemoval{});

    ASSERT_TRUE(std::equal(std::begin(one_by_one),
                           std::end(one_by_one),
                           std::begin(truth),
                           std::end(truth)));

    ASSERT_TRUE(std::equal(std::begin(original_copy),
                           std::end(original_copy),
                           std::begin(truth),
                           std::end(truth)));
  }

  {
    std::vector<int32_t> truth{5};
    std::vector<int32_t> original_copy{original_values};
    remove_pairs_slow(original_copy, AbsDistRemoval{}, truth.size());
    remove_one_pair(one_by_one, AbsDistRemoval{});

    ASSERT_TRUE(std::equal(std::begin(one_by_one),
                           std::end(one_by_one),
                           std::begin(truth),
                           std::end(truth)));

    ASSERT_TRUE(std::equal(std::begin(original_copy),
                           std::end(original_copy),
                           std::begin(truth),
                           std::end(truth)));
  }
}

TEST(AdjacenyPairRemoval, Slow_BounceAround)
{
  const std::vector<int32_t> original_values{0, 5, 8, 9, 10};
  std::vector<int32_t> one_by_one{original_values};
  {
    std::vector<int32_t> truth{0, 5, 8, 10};
    std::vector<int32_t> original_copy{original_values};
    remove_pairs_slow(original_copy, AbsDistRemoval{}, truth.size());
    remove_one_pair(one_by_one, AbsDistRemoval{});

    ASSERT_TRUE(std::equal(std::begin(one_by_one),
                           std::end(one_by_one),
                           std::begin(truth),
                           std::end(truth)));

    ASSERT_TRUE(std::equal(std::begin(original_copy),
                           std::end(original_copy),
                           std::begin(truth),
                           std::end(truth)));
  }

  {
    std::vector<int32_t> truth{0, 5, 9};
    std::vector<int32_t> original_copy{original_values};
    remove_pairs_slow(original_copy, AbsDistRemoval{}, truth.size());
    remove_one_pair(one_by_one, AbsDistRemoval{});

    ASSERT_TRUE(std::equal(std::begin(one_by_one),
                           std::end(one_by_one),
                           std::begin(truth),
                           std::end(truth)));

    ASSERT_TRUE(std::equal(std::begin(original_copy),
                           std::end(original_copy),
                           std::begin(truth),
                           std::end(truth)));
  }

  {
    std::vector<int32_t> truth{0, 7};
    std::vector<int32_t> original_copy{original_values};
    remove_pairs_slow(original_copy, AbsDistRemoval{}, truth.size());
    remove_one_pair(one_by_one, AbsDistRemoval{});

    ASSERT_TRUE(std::equal(std::begin(one_by_one),
                           std::end(one_by_one),
                           std::begin(truth),
                           std::end(truth)));

    ASSERT_TRUE(std::equal(std::begin(original_copy),
                           std::end(original_copy),
                           std::begin(truth),
                           std::end(truth)));
  }

  {
    std::vector<int32_t> truth{3};
    std::vector<int32_t> original_copy{original_values};
    remove_pairs_slow(original_copy, AbsDistRemoval{}, truth.size());
    remove_one_pair(one_by_one, AbsDistRemoval{});

    ASSERT_TRUE(std::equal(std::begin(one_by_one),
                           std::end(one_by_one),
                           std::begin(truth),
                           std::end(truth)));

    ASSERT_TRUE(std::equal(std::begin(original_copy),
                           std::end(original_copy),
                           std::begin(truth),
                           std::end(truth)));
  }

  {
    std::vector<int32_t> truth{3};
    std::vector<int32_t> original_copy{original_values};
    remove_pairs_slow(original_copy, AbsDistRemoval{}, truth.size());
    remove_one_pair(one_by_one, AbsDistRemoval{});

    ASSERT_TRUE(std::equal(std::begin(one_by_one),
                           std::end(one_by_one),
                           std::begin(truth),
                           std::end(truth)));

    ASSERT_TRUE(std::equal(std::begin(original_copy),
                           std::end(original_copy),
                           std::begin(truth),
                           std::end(truth)));
  }
}

}  // namespace njm::algorithm
