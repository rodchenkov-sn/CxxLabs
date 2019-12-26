#ifndef TOKEN_OUTPUT_ITERATOR_HPP
#define TOKEN_OUTPUT_ITERATOR_HPP

#include "token.hpp"

class TokenOutputIterator : public std::iterator<std::output_iterator_tag, TokenOutputIterator>
{
public:

  static const size_t MIN_WIDTH = 25;

  TokenOutputIterator(std::ostream&, size_t);

  reference operator = (const Token&);

  reference operator*();
  reference operator++();
  reference operator++(int);
private:
  std::string    buffer_;
  size_t         width_;
  std::ostream*  out_;
  Token::Type    prev_ = Token::Type::None;
};

#endif // TOKEN_OUTPUT_ITERATOR_HPP
