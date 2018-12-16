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

template <class Tag>
class Inspector
{
 public:
  Inspector() { ++num_constructs; };
  ~Inspector() { ++num_destructs; };
  static uint32_t num_constructs;
  static uint32_t num_destructs;
};

template <class Tag>
uint32_t Inspector<Tag>::num_constructs{0U};

template <class Tag>
uint32_t Inspector<Tag>::num_destructs{0U};

TEST(Variant, PoDTypes)
{
  Variant<utility::TaggedType<X, int32_t>, utility::TaggedType<Y, float>> variant{std::in_place_type<X>, 7};
  EXPECT_EQ(variant.index(), 0);
  visit(variant, [] (auto value)
        {
          constexpr bool is_X = std::is_same_v<std::decay_t<decltype(value)>, int32_t>;
          EXPECT_TRUE(is_X);
          EXPECT_EQ(value, 7);
        });

  variant.emplace(Y{}, 1.3f);

  EXPECT_EQ(variant.index(), 1);
  visit(variant, [] (auto value)
        {
          constexpr bool is_Y = std::is_same_v<std::decay_t<decltype(value)>, float>;
          EXPECT_TRUE(is_Y);
          EXPECT_EQ(value, 1.3f);
        });
}

TEST(Variant, Inspector)
{
  {
    Variant<utility::TaggedType<X, Inspector<X>>, utility::TaggedType<Y, Inspector<Y>>> variant{};
    EXPECT_EQ(Inspector<X>::num_constructs, 1);
    EXPECT_EQ(Inspector<X>::num_destructs, 0);
    EXPECT_EQ(Inspector<Y>::num_constructs, 0);
    EXPECT_EQ(Inspector<Y>::num_destructs, 0);

    variant.emplace(Y{});

    EXPECT_EQ(Inspector<X>::num_constructs, 1);
    EXPECT_EQ(Inspector<X>::num_destructs, 1);
    EXPECT_EQ(Inspector<Y>::num_constructs, 1);
    EXPECT_EQ(Inspector<Y>::num_destructs, 0);

    variant.emplace(Y{});

    EXPECT_EQ(Inspector<X>::num_constructs, 1);
    EXPECT_EQ(Inspector<X>::num_destructs, 1);
    EXPECT_EQ(Inspector<Y>::num_constructs, 2);
    EXPECT_EQ(Inspector<Y>::num_destructs, 1);

    variant.emplace(X{});

    EXPECT_EQ(Inspector<X>::num_constructs, 2);
    EXPECT_EQ(Inspector<X>::num_destructs, 1);
    EXPECT_EQ(Inspector<Y>::num_constructs, 2);
    EXPECT_EQ(Inspector<Y>::num_destructs, 2);
  }

  EXPECT_EQ(Inspector<X>::num_constructs, 2);
  EXPECT_EQ(Inspector<X>::num_destructs, 2);
  EXPECT_EQ(Inspector<Y>::num_constructs, 2);
  EXPECT_EQ(Inspector<Y>::num_destructs, 2);
}

}  // namespace njm::containers
