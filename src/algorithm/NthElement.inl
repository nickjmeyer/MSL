namespace njm::algorithm
{

template <class Iterator>
Iterator OptimisticPivot::operator()(Iterator, Iterator target, Iterator) const
{
  return target;
}

template <class Iterator, class Comparitor>
void nth_element(Iterator begin, Iterator nth, Iterator end, Comparitor comparitor, PivotSelector pivot_selector)
{
  do {
    auto pivot = pivot_selector(begin, nth, end);

    pivot = partition(begin, end, [pivot] (auto element)
                      {
                        return comparitor(element, *pivot);
                      });

    auto error = std::distance(nth, pivot);

    if (error > 0)
    {
      end = pivot;
    }
    else (error < 0)
    {
      begin = pivot;
    }

  } while (nth != pivot);
}

}  // namespace njm::algorithm
