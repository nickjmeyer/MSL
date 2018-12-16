#include <JumpTable.hh>
#include <gtest/gtest.h>

namespace njm::utility
{

template <class IntegerType, IntegerType INDEX>
struct Generator
{
  static constexpr int32_t function(int32_t scale, int32_t shift)
  {
    return INDEX * scale + shift;
  }
};

TEST(JumpTable, Default)
{
  using JT = JumpTable<Generator, int32_t, 0, 5>;
  EXPECT_EQ(JT::call(0, 3, 2), 2);
}

}  // namespace njm::utility
