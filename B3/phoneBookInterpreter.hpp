#ifndef PHONE_BOOK_INTERPRETER_HPP
#define PHONE_BOOK_INTERPRETER_HPP

#include <functional>
#include <string>
#include <unordered_map>

class PhoneBookInterface;

class PhoneBookInterpreter
{
public:

  using Instruction = std::function<std::string(PhoneBookInterface&)>;
  static Instruction interpret(const std::string& cmd);

private:

  static Instruction parse_(std::string);

  static Instruction parse_add_(std::string&);
  static Instruction parse_store_(std::string&);
  static Instruction parse_insert_(std::string&);
  static Instruction parse_delete_(std::string&);
  static Instruction parse_show_(std::string&);
  static Instruction parse_move_(std::string&);

  static std::string extract_str_(std::string&);
  static std::string extract_lexeme_(std::string&);

  static const Instruction invalidInstruction;

  static const std::unordered_map<std::string, std::function<Instruction(std::string&)>> parsers;

};

#endif
