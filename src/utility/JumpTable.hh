#pragma once

#include <TypeTraits.hh>

#include <utility>
#include <cstddef>

namespace njm::utility
{

namespace impl
{
template <class CallableType, class IntegerType, IntegerType Start, IntegerType... Sequence>
constexpr decltype(auto) generate_functions_helper(std::integer_sequence<IntegerType, Sequence...>) noexcept;

template <class CallableType, class IntegerType, IntegerType Start, IntegerType End>
constexpr decltype(auto) generate_functions() noexcept;
}  // namespace impl


template <template <class, auto> class Generator, class IntegerType, IntegerType Start, IntegerType End>
class JumpTable
{
 public:
  template <class... Args>
  static constexpr decltype(auto) call(IntegerType index, Args&&... args);
};

template <class GeneratorHelper>
struct JTHelper
{
  template <class IntegerType, IntegerType INDEX>
  using Helper = typename GeneratorHelper::template Helper<IntegerType, INDEX>;

  template <class IntegerType, IntegerType Start, IntegerType End>
  using Type = JumpTable<Helper, IntegerType, Start, End>;
};

}

#include <JumpTable.inl>
