#pragma once

#include <functional>
#include <utility>

namespace njm::utility
{

template <class First, class Comparitor>
constexpr decltype(auto) compare(Comparitor&&, First&& first)
{
  return std::forward<First>(first);
}

template <class First, class Second, class... Args, class Comparitor>
constexpr decltype(auto) compare(Comparitor&& comparitor, First&& first, Second&& second, Args&&... args)
{
  const bool result = comparitor(first, second);
  return compare(std::forward<Comparitor>(comparitor), result ? std::forward<First>(first) : std::forward<Second>(second), std::forward<Args>(args)...);
}

template <class... Args>
constexpr decltype(auto) min(Args&&... args)
{
  return compare(std::less{}, std::forward<Args>(args)...);
}

template <class... Args>
constexpr decltype(auto) max(Args&&... args)
{
  return compare(std::greater{}, std::forward<Args>(args)...);
}

}  // namespace njm::utility
