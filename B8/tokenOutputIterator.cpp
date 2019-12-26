#include "tokenOutputIterator.hpp"

#include <stdexcept>
#include <iostream>

TokenOutputIterator::TokenOutputIterator(std::ostream& out, size_t width):
  width_(width),
  out_(&out)
{
  if (width_ < MIN_WIDTH) {
    throw std::invalid_argument{ "width must be at least " + std::to_string(MIN_WIDTH) };
  }
}

TokenOutputIterator::reference TokenOutputIterator::operator=(const Token& current)
{
  std::string toPrint;
  switch (current.type()) {
  case Token::Type::Word:
  case Token::Type::Number: {
    if (buffer_.empty()) {
      buffer_ = current.lexeme();
    } else if (buffer_.length() + 1 + current.length() > width_) {
      toPrint = buffer_ + '\n';
      buffer_ = current.lexeme();
    } else {
      buffer_ = buffer_ + " " + current.lexeme();
    }
    prev_ = current.type();
    break;
  }
  case Token::Type::NumberTail: {
    if (buffer_.size() + current.length() > width_) {
      auto flushUntil = buffer_.find_last_of(' ');
      toPrint = buffer_.substr(0, flushUntil) + "\n";
      buffer_.erase(0, flushUntil + 1);
    }
    buffer_ += current.lexeme();
    break;
  }
  case Token::Type::DashTail: {
    buffer_.pop_back();
    // fallthrough
  }
  case Token::Type::Dash: {
    if (buffer_.size() + 4 > width_) {
      auto flushUntil = buffer_.find_last_of(' ');
      toPrint = buffer_.substr(0, flushUntil) + "\n";
      buffer_.erase(0, flushUntil + 1);
    }
    buffer_ += " ---";
    prev_ = Token::Type::Dash;
    break;
  }
  case Token::Type::Punctuation: {
    if (buffer_.size() + 1 > width_)  {
      auto flushUntil = buffer_.find_last_of(' ');
      toPrint = buffer_.substr(0, flushUntil) + "\n";
      buffer_.erase(0, flushUntil + 1);
    }
    buffer_ += current.lexeme();
    prev_ = Token::Type::Punctuation;
    break;
  }
  case Token::Type::Unknown: {
    break;
  }
  case Token::Type::Eof: {
    *out_ << buffer_ << "\n";
    return *this;
  }
  default:;
  }
  *out_ << toPrint;
  return *this;
}

TokenOutputIterator::reference TokenOutputIterator::operator*()
{
  return *this;
}

TokenOutputIterator::reference TokenOutputIterator::operator++()
{
  return *this;
}

TokenOutputIterator::reference TokenOutputIterator::operator++(int)
{
  return *this;
}
