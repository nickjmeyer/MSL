#pragma once

#include <utility>

namespace njm::containers
{

template <class TagType, class ValueType>
struct TupleTag
{
  using Tag = TagType;
  using Value = ValueType;
};

template <class... TupleTags>
class TaggedTuple
{
 public:
  TaggedTuple() = default;
  TaggedTuple(const TaggedTuple&) = default;
  TaggedTuple(TaggedTuple&&) = default;

  template <class... Args>
  TaggedTuple(Args&&... args) : tuple_{std::forward<Args>(args)...} {}

  template <class Tag>
  decltype(auto) get(Tag) { return tuple_.get(Tag{}); }

  template <class Tag>
  decltype(auto) get(Tag) const { return tuple_.get(Tag{}); }

 private:
  template <class TupleTag>
  struct Element
  {
    using Tag = typename TupleTag::Tag;
    using Value = typename TupleTag::Value;

    Element() : value_{} {}

    template <class Value_t>
    Element(Value_t&& value) : value_{std::forward<Value_t>(value)} {}

    Value& get(Tag) { return value_; }
    const Value& get(Tag) const { return value_; };

   private:
    Value value_;
  };

  class Tuple : public Element<TupleTags>...
  {
 public:
        Tuple()
        : Element<TupleTags>{}... {}

    template <class... Args>
        Tuple(Args&&... args)
        : Element<TupleTags>{std::forward<Args>(args)}... {}
    using Element<TupleTags>::get...;
  };

  Tuple tuple_;
};

}  // njm::containers
