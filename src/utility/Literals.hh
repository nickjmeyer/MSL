#pragma once

#include <TypeTraits.hh>

namespace njm
{

inline namespace literals
{

template <class Char, Char... chars>
auto operator"" _s()
{
  return utility::ValueList<chars...>{};
}

}  // namespace literals

} // namespace njm
