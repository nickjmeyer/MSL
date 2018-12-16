#include <TypeTraits.hh>
#include <array>

namespace njm::utility
{

template <template <class, auto> class Generator, class IntegerType, class... Args>
struct JumpTableCallable
{
  template <IntegerType INDEX>
  static constexpr decltype(auto) call(Args&&... args)
  {
    return Generator<IntegerType, INDEX>::function(std::forward<Args>(args)...);
  }
};

namespace impl
{

template <class CallableType, class IntegerType, IntegerType Start, IntegerType... Sequence>
constexpr decltype(auto) generate_functions_helper(std::integer_sequence<IntegerType, Sequence...>) noexcept
{
  using FunctionType = decltype(CallableType::template call<Start>);
  static_assert(all_same_type(TypeList<decltype(CallableType::template call<Start+Sequence>)...>{}));

  return std::array{CallableType::template call<Start+Sequence>...};
}

template <class CallableType, class IntegerType, IntegerType Start, IntegerType End>
constexpr decltype(auto) generate_functions() noexcept
{
  static_assert(End >= Start, "End must be at least Start");
  return generate_functions_helper<CallableType, IntegerType, Start>(std::make_integer_sequence<IntegerType, End - Start>());
}

}  // namespace impl


template <template <class, auto> class Generator, class IntegerType, IntegerType Start, IntegerType End>
template <class... Args>
constexpr decltype(auto) JumpTable<Generator, IntegerType, Start, End>::call(IntegerType index, Args&&... args)
{
  using CallableType = JumpTableCallable<Generator, IntegerType, Args...>;
  constexpr auto functions = impl::generate_functions<CallableType, IntegerType, Start, End>();
  if (index < Start || index >= End)
  {
    throw std::invalid_argument("Start must be in [Start, End).");
  }

  return functions[static_cast<size_t>(index - Start)](std::forward<Args>(args)...);
}

}  // njm::utility
