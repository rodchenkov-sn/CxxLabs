#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

class Token
{
public:

  enum class Type
  {
    Word, Number, NumberTail, Dash, DashTail, Punctuation, Unknown, None, Eof
  };

  static const size_t MAX_WORD_LENGTH = 20;

  Token() = default;
  explicit Token(Type);

  friend std::istream& operator >> (std::istream&, Token&);
  friend std::ostream& operator << (std::ostream&, const Token&);

  Type               type()   const noexcept;
  size_t             length() const noexcept;
  const std::string& lexeme() const noexcept;
  const std::string& tail()   const noexcept;

  size_t col = 0, row = 0;

private:

  static bool read_word_(std::istream&, std::string&);
         bool read_num_(std::istream&, std::string&);
         bool read_num_tail_(std::istream&, std::string&);

  std::string lexeme_;
  std::string tail_;
  Type        type_ = Type::None;
  bool        may_have_tail_ = false;

  char decimal_point_ = '\0';

};

#endif // TOKEN_HPP
