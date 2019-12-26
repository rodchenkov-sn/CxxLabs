#include "tokenValidator.hpp"

#include <algorithm>
#include <stdexcept>
#include <iostream>

const TokenValidator::status_t& TokenValidator::status() const noexcept
{
  return status_;
}

Token TokenValidator::operator()(const Token& current)
{
  switch (current.type()) {
  case Token::Type::Word:
  case Token::Type::Number:
    prev_ = current;
    return current;
  case Token::Type::Dash:
    if (prev_.type() == Token::Type::None || prev_.type() == Token::Type::Dash || prev_.type() == Token::Type::DashTail
      || (prev_.type() == Token::Type::Punctuation && prev_.lexeme() != ",")) {
      status_.ok = false;
      status_.errors.push_back("unexpected dash at row: " + std::to_string(current.row) + ", col: " + std::to_string(current.col));
    }
    prev_ = current;
    return current;
  case Token::Type::Punctuation:
    if (prev_.type() == Token::Type::None || prev_.type() == Token::Type::Punctuation 
      || prev_.type() == Token::Type::Dash || prev_.type() == Token::Type::DashTail) {
      status_.ok = false;
      status_.errors.push_back("unexpected punctuation at row: " + std::to_string(current.row) + ", col: " + std::to_string(current.col));
    }
    prev_ = current;
    return current;
  case Token::Type::Unknown:
    status_.ok = false;
    status_.errors.push_back("unexpected token ('" + current.lexeme() + "') at row: " + std::to_string(current.row) + ", col: " + std::to_string(current.col));
    prev_ = current;
    return current;
  case Token::Type::NumberTail:
    if (prev_.type() != Token::Type::Number) {
      status_.ok = false;
      status_.errors.push_back("unexpected decimal point at row: " + std::to_string(current.row) + ", col: " + std::to_string(current.col));
    }
    prev_ = current;
    return current;
  case Token::Type::DashTail:
    if (prev_.type() != Token::Type::Word) {
      status_.ok = false;
      status_.errors.push_back("unexpected '--' at row: " + std::to_string(current.row) + ", col: " + std::to_string(current.col));
    }
    prev_ = current;
    return current;
  default: return current;
  }
}

std::ostream& operator<<(std::ostream& stream, const TokenValidator::status_t& stage)
{
  std::ostream::sentry sentry{ stream };
  if (!sentry) {
    return stream;
  }
  if (stage.ok) {
    stream << "Status: ok.\n";
  }
  else {
    stream << "Status: failure.\nErrors:\n";
    for (size_t i = 0; i < stage.errors.size(); i++) {
      stream << i + 1 << ": " << stage.errors.at(i) << "\n";
    }
  }
  return stream;
}
