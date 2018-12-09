#include "../tagged_tuple.hh"
#include <gtest/gtest.h>

#include <cstdint>

#include <iostream>

using namespace njm::containers;

struct X
{
};

struct Y
{
};

using XTag = TupleTag<X, float>;
using YTag = TupleTag<Y, int32_t>;

using TT = TaggedTuple<XTag, YTag >;

TEST(TaggedTuple, Default)
{
  TT t{};
  EXPECT_EQ(t.get(X{}), float{});
}
