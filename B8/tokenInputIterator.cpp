#include "tokenInputIterator.hpp"

#include <iostream>
#include <algorithm>

#include "ioUtils.hpp"

TokenInputIterator::TokenInputIterator() :
  eof_(true),
  last_(true)
{
}

TokenInputIterator::TokenInputIterator(std::istream& stream) :
  managed_(stream),
  eof_(false),
  last_(false),
  flag_guard_(std::make_shared<FlagGuard>(stream))
{
  stream >> std::noskipws;
  auto t = readUntil(stream, [](char c) { return !isspace(c); });
  update_position_(t);
}

std::istream_iterator<Token>::value_type TokenInputIterator::operator*()
{
  if (last_) {
    eof_ = true;
    return Token{ Token::Type::Eof };
  }
  auto t = *managed_;

  t.col = col_;
  t.row = row_;

  col_ += t.length();
  update_position_(t.tail());

  if (managed_ == std::istream_iterator<Token>{}) {
    last_ = true;
  }
  if (t.type() == Token::Type::Eof) {
    eof_ = true;
  }
  return t;
}

TokenInputIterator& TokenInputIterator::operator++()
{
  if (!eof_) {
    ++managed_;
  }
  return *this;
}

TokenInputIterator TokenInputIterator::operator++(int)
{
  return ++ * this;
}

bool TokenInputIterator::operator!=(const TokenInputIterator& rhs) const
{
  if (eof_ == rhs.eof_) {
    return false;
  }
  return true;
}

bool TokenInputIterator::operator==(const TokenInputIterator& rhs) const
{
  return !(*this != rhs);
}

void TokenInputIterator::update_position_(const std::string& t)
{
  std::for_each(
    t.begin(), t.end(), [&](char c) {
      if (isblank(c)) {
        ++col_;
      }
      else if (c == '\n') {
        ++row_;
        col_ = 1;
      } else if (c == '\r') {
        col_ = 1;
      }
    });
}
