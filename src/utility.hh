#pragma once

#include <cstddef>

namespace njm::utility
{

template <class... Element>
struct TypeList
{
};

template <class Type_t>
struct TypeWrapper
{
  using Type = Type_t;
};

template <class... TypesA, class... TypesB>
constexpr decltype(auto) operator+(TypeList<TypesA...>, TypeList<TypesB...>)
{
  return TypeList<TypesA..., TypesB...>{};
}

template <class Type>
constexpr decltype(auto) to_type_wrapper(TypeList<Type>)
{
  return TypeWrapper<Type>{};
}

template <class Tag, class... TaggedTypes>
constexpr decltype(auto) type_for_tag(Tag, TaggedTypes...)
{
  return to_type_wrapper((std::conditional_t<
                         std::is_same_v<typename TaggedTypes::Tag, Tag>,
                         TypeList<typename TaggedTypes::Value>,
                         TypeList<>
                          >{} + ...));
}

template <class FirstElement, class... Rest>
constexpr decltype(auto) first_element(TypeList<FirstElement, Rest...>)
{
  return TypeWrapper<FirstElement>();
}

namespace impl
{

template <class Tag, class... Tags, size_t... Ints>
constexpr decltype(auto) index_of(Tag, TypeList<Tags...>, std::index_sequence<Ints...>)
{
  return typename decltype(to_type_wrapper((std::conditional_t<
                                           std::is_same_v<Tag, Tags>,
                                           TypeList<std::integral_constant<size_t, Ints>>,
                                            TypeList<>>{} + ...)))::Type::value();
}

}  // namespace impl

template <class Tag, class... Tags>
constexpr size_t index_of(Tag, TypeList<Tags...>)
{
  return impl::index_of(Tag{}, TypeList<Tags...>{}, std::make_index_sequence<sizeof...(Tags)>());
}

template <class Tag, class... TaggedTypes>
using TypeForTag = typename decltype(type_for_tag(Tag{}, TaggedTypes{}...))::Type;

}  // namespace njm::utility
