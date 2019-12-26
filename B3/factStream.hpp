#ifndef FACT_STREAM_HPP
#define FACT_STREAM_HPP
#include <iterator>

constexpr uint8_t operator "" _uc(unsigned long long x)
{
  return static_cast<uint8_t>(x);
}

class FactStream
{
public:

  using ValueType = uint64_t;
  using DifferenceType = int64_t;
  using SizeType = uint8_t;

  class Iterator : public std::iterator<std::bidirectional_iterator_tag, ValueType, DifferenceType, ValueType*, ValueType>
  {
  public:
    Iterator& operator++();
    Iterator  operator++(int);
    Iterator& operator--();
    Iterator  operator--(int);
    bool operator==(const Iterator&) const;
    bool operator!=(const Iterator&) const;
    reference operator*() const;
  private:

    friend class FactStream;
    Iterator(SizeType, ValueType, SizeType, SizeType);
    SizeType   curr_;
    ValueType  prod_;
    SizeType   low_;
    SizeType   high_;
  };

  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstIterator = Iterator;
  using ConstReverseIterator = ReverseIterator;

  explicit FactStream(SizeType);
  FactStream(SizeType, SizeType);

  Iterator begin() const;
  Iterator   end() const;

  ReverseIterator rbegin() const;
  ReverseIterator   rend() const;

  ConstIterator cbegin() const;
  ConstIterator   cend() const;

  ConstReverseIterator crbegin() const;
  ConstReverseIterator   crend() const;

  bool  empty() const noexcept;
  size_t size() const noexcept;

private:

  static constexpr SizeType max_end_() noexcept;
  static void check_limits_(SizeType begin, SizeType end);
  static ValueType fact_(SizeType) noexcept;

  SizeType   begin_;
  SizeType   end_;
  ValueType  begin_val_;
  ValueType  end_val_;
};

#endif // FACT_STREAM_HPP
