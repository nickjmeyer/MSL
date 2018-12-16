#include <Variant.hh>
#include <gtest/gtest.h>

namespace njm::containers
{

struct X
{
};

struct Y
{
};

TEST(Variant, Default)
{
  Variant<utility::TaggedType<X, int32_t>, utility::TaggedType<Y, float>> variant{std::in_place_type<X>, 7};
  EXPECT_EQ(variant.index(), 0);
  visit(variant, [] (auto value)
        {
          constexpr bool is_X = std::is_same_v<std::decay_t<decltype(value)>, int32_t>;
          EXPECT_TRUE(is_X);
        });
}

}  // namespace njm::containers
