#include <TaggedTuple.hh>
#include <TypeTraits.hh>
#include <gtest/gtest.h>

#include <cstdint>

#include <iostream>

namespace njm::containers
{

struct X
{
};

struct Y
{
};

using XTag = utility::TaggedType<X, float>;
using YTag = utility::TaggedType<Y, int32_t>;

using TT = TaggedTuple<XTag, YTag >;

TEST(TaggedTuple, Default)
{
  TT t{};
  EXPECT_EQ(t.get(X{}), float{});
}

}  // namespace njm::containers
