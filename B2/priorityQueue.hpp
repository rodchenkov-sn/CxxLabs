#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include <list>
#include <stddef.h>

template <typename T>
class PriorityQueue
{
  enum class Priority
  {
    High, Normal, Low
  };

public:

  void put(const T&, Priority);
  template <typename Handler>
  bool applyFront(Handler);
  bool popFront() noexcept;
  void accelerate();

  size_t size() const noexcept;
  bool empty() const noexcept;

  static Priority low() noexcept;
  static Priority normal() noexcept;
  static Priority high() noexcept;

private:

  std::list<T> high_;
  std::list<T> normal_;
  std::list<T> low_;
};

template <typename T>
void PriorityQueue<T>::put(const T& element, Priority priority)
{
  switch (priority) {
  case Priority::High:
    high_.push_back(element);
    break;
  case Priority::Normal:
    normal_.push_back(element);
    break;
  case Priority::Low:
    low_.push_back(element);
    break;
  }
}

template <typename T>
template <typename Handler>
bool PriorityQueue<T>::applyFront(Handler fun)
{
  if (!high_.empty()) {
    fun(high_.front());
    high_.pop_front();
    return true;
  }
  if (!normal_.empty()) {
    fun(normal_.front());
    normal_.pop_front();
    return true;
  }
  if (!low_.empty()) {
    fun(low_.front());
    low_.pop_front();
    return true;
  }
  return false;
}

template <typename T>
bool PriorityQueue<T>::popFront() noexcept
{
  if (!high_.empty()) {
    high_.pop_front();
    return true;
  }
  if (!normal_.empty()) {
    normal_.pop_front();
    return true;
  }
  if (!low_.empty()) {
    low_.pop_front();
    return true;
  }
  return false;
}

template <typename T>
void PriorityQueue<T>::accelerate()
{
  high_.splice(high_.end(), low_);
}

template <typename T>
size_t PriorityQueue<T>::size() const noexcept
{
  return high_.size() + normal_.size() + low_.size();
}

template <typename T>
bool PriorityQueue<T>::empty() const noexcept
{
  return high_.empty() && normal_.empty() && low_.empty();
}

template <typename T>
typename PriorityQueue<T>::Priority PriorityQueue<T>::low() noexcept
{
  return Priority::Low;
}

template <typename T>
typename PriorityQueue<T>::Priority PriorityQueue<T>::normal() noexcept
{
  return Priority::Normal;
}

template <typename T>
typename PriorityQueue<T>::Priority PriorityQueue<T>::high() noexcept
{
  return Priority::High;
}

#endif // PRIORITY_QUEUE_HPP
