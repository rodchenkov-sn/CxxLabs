#ifndef TOKEN_VALIDATOR_HPP
#define TOKEN_VALIDATOR_HPP

#include <vector>
#include "token.hpp"

class TokenValidator
{
public:

  struct status_t
  {
    bool                     ok;
    std::vector<std::string> errors;
  };

  const status_t& status() const noexcept;
  Token operator() (const Token&);

private:
  Token        prev_     { Token::Type::None };
  status_t     status_   { true, {} };
};

std::ostream& operator<<(std::ostream&, const TokenValidator::status_t&);

#endif // TOKEN_VALIDATOR_HPP
