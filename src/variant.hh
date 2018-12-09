#pragma once

#include "utility.hh"

#include <new>
#include <type_traits>

namespace njm::containers
{

template <class... VariantTags>
class Variant
{

 public:

  template <class Tag, class... Args>
  Variant(std::in_place_t<Tag>, Args&&... args)
  {
    construct(Tag{}, std::forward<Args>{args}...);
  }

  Variant()
  {
    using FirstTag = typename decltype(first_element(utility::TypeList<VariantTags...>{}))::Type;
    using TagType = typename FirstTag::TagType;

    construct(TagType{});
  }

  ~Variant()
  {
  }

  template <class Tag>
  auto& get(Tag) { return std::launder(std::reinterpret_cast<std::add_pointer_t<utility::TypeForTag<Tag, VariantTag>>>(bytes_.data())); }

  template <class Tag>
  auto& get(Tag) const { return std::launder(std::reinterpret_cast<std::add_const_t<std::add_pointer_t<utility::TypeForTag<Tag, VariantTag>>>>(bytes_.data())); }

  template <class Tag>
  void destruct(Tag)
  {
    get(Tag{}).~utility::TypeForTag<Tag, VariantTags...>();
  }

  template <class Tag, class... Args>
  void construct(Tag, Args&&... args)
  {
    using ValueType = typename decltype(utility::TypeForTag<Tag, VariantTags...>())::Type;
    new (std::addressof(get(Tag{}).~) {std::forward<Args>{args}...};
  }

  template <class Tag, class... Args>
  void emplace(Tag, Args&&... args)
  {

    destruct(Tag{});

    construct(Tag{}, std::forward<Args>{args}...);
  }

 private:
  uint32_t index_;
  std::array<std::byte, utility::max(sizeof(typename VariantTags::ValueType)...)> bytes_;
};


}  // namespace njm::containers
