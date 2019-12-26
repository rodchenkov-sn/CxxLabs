#ifndef TOKEN_INPUT_ITERATOR_HPP
#define TOKEN_INPUT_ITERATOR_HPP

#include "token.hpp"
#include "ioUtils.hpp"

#include <iterator>
#include <memory>

class TokenInputIterator : public std::iterator<std::input_iterator_tag, Token, std::ptrdiff_t, const Token*, const Token&>
{
public:

  using Ti = std::istream_iterator<Token>;

  TokenInputIterator();
  explicit TokenInputIterator(std::istream&);

  value_type operator* ();
  TokenInputIterator& operator ++();
  TokenInputIterator  operator++(int);
  bool operator != (const TokenInputIterator& rhs) const;
  bool operator == (const TokenInputIterator& rhs) const;

private:

  void update_position_(const std::string&);

  std::istream_iterator<Token> managed_;
  bool eof_;
  bool last_;
  size_t col_ = 1;
  size_t row_ = 1;
  std::shared_ptr<FlagGuard> flag_guard_;
};

#endif // TOKEN_INPUT_ITERATOR_HPP
