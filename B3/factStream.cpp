#include "factStream.hpp"

#include <limits>


FactStream::Iterator& FactStream::Iterator::operator++()
{
  if (curr_ == high_) {
    throw std::out_of_range{ "FactStream::Iterator out of range" };
  }
  ++curr_;
  prod_ *= curr_;
  return *this;
}

FactStream::Iterator FactStream::Iterator::operator++(int)
{
  const auto tmp(*this);
  ++* this;
  return tmp;
}

FactStream::Iterator& FactStream::Iterator::operator--()
{
  if (curr_ == low_) {
    throw std::out_of_range{ "FactStream::Iterator out of range" };
  }
  if (curr_ > 0) {
    prod_ /= curr_;
  }
  --curr_;
  return *this;
}

FactStream::Iterator FactStream::Iterator::operator--(int)
{
  const auto tmp(*this);
  --* this;
  return tmp;
}

bool FactStream::Iterator::operator==(const Iterator& other) const
{
  return curr_ == other.curr_;
}

bool FactStream::Iterator::operator!=(const Iterator& other) const
{
  return !(*this == other);
}

FactStream::Iterator::reference FactStream::Iterator::operator*() const
{
  if (curr_ == high_) {
    throw std::runtime_error{ "invalid dereferencing" };
  }
  return prod_;
}


bool FactStream::empty() const noexcept
{
  return false;
}

size_t FactStream::size() const noexcept
{
  return end_ - begin_ + 1_uc;
}

constexpr FactStream::SizeType FactStream::max_end_() noexcept
{
  ValueType prod = 1;
  SizeType  i = 1;
  while (i < std::numeric_limits<ValueType>::max() / prod) {
    prod *= i;
    ++i;
  }
  return i - 2;
}

void FactStream::check_limits_(SizeType begin, SizeType end)
{
  if (begin > end) {
    throw std::invalid_argument{ "begin value must be less than end value" };
  }
  constexpr auto max = max_end_();
  if (end > max || begin > max) {
    throw std::invalid_argument{ "end value is too big" };
  }
}

FactStream::ValueType FactStream::fact_(SizeType x) noexcept
{
  ValueType prod = 1;
  for (SizeType i = 1; i <= x; i++) {
    prod *= i;
  }
  return prod;
}

FactStream::Iterator::Iterator(SizeType curr, ValueType prod, SizeType low, SizeType high) :
  curr_(curr),
  prod_(prod),
  low_(low),
  high_(high)
{
}

FactStream::FactStream(SizeType end) :
  begin_(1),
  end_(end)
{
  check_limits_(begin_, end_);
  begin_val_ = 1;
  end_val_ = fact_(end_ + 1);
}

FactStream::FactStream(SizeType begin, SizeType end) :
  begin_(begin),
  end_(end)
{
  check_limits_(begin_, end_);
  begin_val_ = fact_(begin_);
  end_val_ = fact_(end_ + 1);
}

FactStream::Iterator FactStream::begin() const
{
  return Iterator(begin_, begin_val_, begin_, end_ + 1_uc);
}

FactStream::Iterator FactStream::end() const
{
  return Iterator(end_ + 1_uc, end_val_, begin_, end_ + 1_uc);
}


FactStream::ReverseIterator FactStream::rbegin() const
{
  return std::make_reverse_iterator(end());
}

FactStream::ReverseIterator FactStream::rend() const
{
  return std::make_reverse_iterator(begin());
}

FactStream::ConstIterator FactStream::cbegin() const
{
  return begin();
}

FactStream::ConstIterator FactStream::cend() const
{
  return end();
}

FactStream::ConstReverseIterator FactStream::crbegin() const
{
  return rbegin();
}

FactStream::ConstReverseIterator FactStream::crend() const
{
  return rend();
}
