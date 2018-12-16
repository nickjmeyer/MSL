#pragma once

#include <TypeTraits.hh>
#include <JumpTable.hh>
#include <Algorithm.hh>

#include <new>
#include <type_traits>

namespace njm::containers
{

template <class... VariantTags>
class Variant;

template <class... ElementTypes>
struct DestructorGenerator
{
  template <class IntegerType, IntegerType INDEX>
  struct Helper
  {
    using Type = typename decltype(utility::get_type_at_index(std::integral_constant<IntegerType, INDEX>{}, utility::TypeList<ElementTypes...>{}))::Type;
    using Tag = typename Type::Tag;
    using Value = typename Type::Value;

    static constexpr void function(Variant<ElementTypes...>& variant)
    {
      variant.template get(Tag{}).~Value();
    }
  };
};

template <class VisitorType, class... ElementTypes>
struct VisitorGenerator
{
  template <class IntegerType, IntegerType INDEX>
  struct Helper
  {
    using Type = typename decltype(utility::get_type_at_index(std::integral_constant<IntegerType, INDEX>{},utility::TypeList<ElementTypes...>{}))::Type;

    template <class VariantType>
    static constexpr decltype(auto) function(VariantType&& variant, VisitorType&& visitor)
    {
      static_assert(std::is_same_v<Variant<ElementTypes...>, std::decay_t<VariantType>>);
      return visitor(variant.get(typename Type::Tag{}));
    }
  };
};

template <class VisitorType, class... ElementTypes>
constexpr decltype(auto) create_visitor_jump_table(utility::TypeWrapper<VisitorType>,
                                                   utility::TypeWrapper<Variant<ElementTypes...>>) noexcept
{
  return utility::TypeWrapper<typename utility::JTHelper<VisitorGenerator<VisitorType, ElementTypes...>>::template Type<size_t, 0, sizeof...(ElementTypes)>>{};
}

template <class... VariantTags>
class Variant
{
 private:
    template <class IntegerType, IntegerType INDEX>
    using DestructorHelper = typename DestructorGenerator<VariantTags...>::template Helper<IntegerType, INDEX>;
 public:
  template <class Tag, class... Args>
  Variant(std::in_place_type_t<Tag>, Args&&... args)
  {
    construct(Tag{}, std::forward<Args>(args)...);
  }

  Variant()
  {
    using FirstTag = typename decltype(first_element(utility::TypeList<VariantTags...>{}))::Type;
    using Tag = typename FirstTag::Tag;

    construct(Tag{});
  }

  ~Variant()
  {
    destruct();
  }

  template <class Tag>
  constexpr decltype(auto) pointer(Tag)
  {
    return reinterpret_cast<std::add_pointer_t<utility::TypeForTag<Tag, VariantTags...>>>(&bytes_);
  }

  template <class Tag>
  auto& unsafe_get(Tag)
  {
    return *std::launder(pointer(Tag{}));
  }

  template <class Tag>
  auto& unsafe_get(Tag) const
  {
    return *std::launder(pointer(Tag{}));
  }

  template <class Tag>
  auto& get(Tag)
  {
    if (index() != index_of(Tag{},utility::TypeList<typename VariantTags::Tag...>{}))
    {
      throw std::invalid_argument("Invalid variant access.");
    }
    return unsafe_get(Tag{});
  }

  template <class Tag>
  auto& get(Tag) const
  {
    if (index() != index_of(Tag{},utility::TypeList<typename VariantTags::Tag...>{}))
    {
      throw std::invalid_argument("Invalid variant access.");
    }
    return unsafe_get(Tag{});
  }

  void destruct()
  {
    using JT = utility::JumpTable<DestructorHelper, size_t, 0U, sizeof...(VariantTags)>;
    if (index_ < sizeof...(VariantTags))
    {
      JT::call(index(), *this);
      index_ = sizeof...(VariantTags);
    }
  }

  size_t index()
  {
    return index_;
  }

  template <class Tag, class... Args>
  void emplace(Tag, Args&&... args)
  {
    destruct();

    construct(Tag{}, std::forward<Args>(args)...);
  }

 private:
  template <class Tag, class... Args>
  void construct(Tag, Args&&... args)
  {
    using Value = utility::TypeForTag<Tag, VariantTags...>;

    new (pointer(Tag{})) Value{std::forward<Args>(args)...};

    index_ = index_of(Tag{},utility::TypeList<typename VariantTags::Tag...>{});
  }

  size_t index_;
  std::aligned_storage<utility::max(sizeof(typename VariantTags::Value)...), utility::max(alignof(typename VariantTags::Value)...)> bytes_;
};

template <class Callable, class VariantType>
decltype(auto) visit(VariantType&& variant, Callable&& callable)
{
  using JT = typename decltype(create_visitor_jump_table(utility::TypeWrapper<Callable>{}, utility::TypeWrapper<std::decay_t<VariantType>>{}))::Type;
  return JT::call(variant.index(), std::forward<VariantType>(variant), std::forward<Callable>(callable));
}

}  // namespace njm::containers
