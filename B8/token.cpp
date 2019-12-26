#include "token.hpp"

#include <iostream>
#include <locale>

#include "ioUtils.hpp"

Token::Token(Type type) :
  type_(type)
{
}

Token::Type Token::type() const noexcept
{
  return type_;
}

size_t Token::length() const noexcept
{
  return lexeme_.length();
}

const std::string& Token::lexeme() const noexcept
{
  return lexeme_;
}

const std::string& Token::tail() const noexcept
{
  return tail_;
}

bool Token::read_word_(std::istream& stream, std::string& word)
{
  while (isalpha(stream.peek()) || stream.peek() == '-') {
    char c;
    stream.get(c);
    word += c;
    if (c == '-' && !isalpha(stream.peek())) {
      break;
    }
  }
  if (word.length() > MAX_WORD_LENGTH) {
    return false;
  }
  return true;
}

bool Token::read_num_(std::istream& stream, std::string& number)
{
  number += readUntil(stream, [](char c) { return !isdigit(c); });
  if (stream.peek() == decimal_point_) {
    may_have_tail_ = true;
  }
  if (number.length() > MAX_WORD_LENGTH) {
    return false;
  }
  return true;
}

bool Token::read_num_tail_(std::istream& stream, std::string& number)
{
  number += readUntil(stream, [](char c) { return !isdigit(c); });
  may_have_tail_ = false;
  if (number.size() > MAX_WORD_LENGTH) {
    return false;
  }
  return true;
}

std::istream& operator>>(std::istream& stream, Token& token)
{
  std::istream::sentry sentry{ stream };
  if (!sentry) {
    token.type_ = Token::Type::Eof;
    return stream;
  }
  if (token.decimal_point_ == '\0') {
    token.decimal_point_ = std::use_facet<std::numpunct<char>>(stream.getloc()).decimal_point();
  }
  Token::Type type;
  std::string lexeme;
  if (stream.peek() == std::char_traits<char>::eof()) {
    token.type_ = Token::Type::Eof;
    return stream;
  }
  if (isalpha(stream.peek())) {
    bool ok = Token::read_word_(stream, lexeme);
    type = ok ? Token::Type::Word : Token::Type::Unknown;
  }
  else if (isdigit(stream.peek())) {
    bool ok = token.read_num_(stream, lexeme);
    type = ok ? Token::Type::Number : Token::Type::Unknown;
  }
  else if (ispunct(stream.peek())) {
    char c;
    stream.get(c);
    lexeme = c;
    if ((c == '+' || c == '-') && isdigit(stream.peek())) {
      bool ok = token.read_num_(stream, lexeme);
      type = ok ? Token::Type::Number : Token::Type::Unknown;
    } else if (c == '-') {
      lexeme += readUntil(stream, [](char c) { return c != '-'; });
      if (lexeme.size() == 2 && token.type() == Token::Type::Word && token.lexeme().back() == '-') {
        type = Token::Type::DashTail;
      } else if (lexeme.size() == 3) {
        type = Token::Type::Dash;
      } else {
        type = Token::Type::Unknown;
      }
    } else if (c == token.decimal_point_ && isdigit(stream.peek()) && token.may_have_tail_) {
      bool ok = token.read_num_tail_(stream, lexeme);
      type = ok && (token.lexeme_.length() + lexeme.length() <= Token::MAX_WORD_LENGTH) ? Token::Type::NumberTail : Token::Type::Unknown;
    } else {
      type = Token::Type::Punctuation;
    }
  } else {
    lexeme = readUntil(stream, [](char c) { return isspace(c); });
    type = Token::Type::Unknown;
  }
  token.tail_ = readUntil(stream, [](char c) {
    return !isspace(c);
  });
  token.lexeme_ = lexeme;
  token.type_ = type;
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const Token& token)
{
  std::ostream::sentry sentry{ stream };
  if (sentry) {
    stream << token.lexeme_;
  }
  return stream;
}
