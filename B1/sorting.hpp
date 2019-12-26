#ifndef SORTING_HPP
#define SORTING_HPP

#include <functional>

namespace details {

  template <typename AccessType>
  void qSort(
    typename AccessType::Container& arr,
    typename AccessType::SizeType b,
    typename AccessType::SizeType e,
    std::function<bool(typename AccessType::Element, typename AccessType::Element)> comparator
  ) {
    if (b == e) {
          return;
    }
    typename AccessType::Element pivot = AccessType::get(arr, b);
    auto lB = b, eB = b;
    auto i = AccessType::inc(b);
    while (i != e) {
      if (comparator(AccessType::get(arr, i), pivot)) {
        lB = AccessType::inc(lB);
        eB = AccessType::inc(eB);
        std::swap(AccessType::get(arr, lB), AccessType::get(arr, i));
        if (lB != eB) {
          std::swap(AccessType::get(arr, eB), AccessType::get(arr, i));
        }
      }
      else if (AccessType::get(arr, i) == pivot) {
        eB = AccessType::inc(eB);
        std::swap(AccessType::get(arr, eB), AccessType::get(arr, i));
      }
      i = AccessType::inc(i);
    }
    std::swap(AccessType::get(arr, b), AccessType::get(arr, lB));
    qSort<AccessType>(arr, b, lB, comparator);
    qSort<AccessType>(arr, AccessType::inc(eB), e, comparator);
  }

} // namespace details

template <template <class> class AccessType, class ContainerType>
void sort(
  ContainerType& arr, 
  std::function<bool(typename ContainerType::reference, typename ContainerType::reference)> comparator)
{
  details::qSort<AccessType<ContainerType>>(arr, AccessType<ContainerType>::begin(arr), AccessType<ContainerType>::end(arr), comparator);
}

#endif // SORTING_HPP
