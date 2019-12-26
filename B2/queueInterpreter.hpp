#ifndef QUEUE_INTERPRETER_HPP
#define QUEUE_INTERPRETER_HPP

#include <string>
#include <unordered_map>
#include <functional>

#include "priorityQueue.hpp"

class QueueInterpreter
{
  using Queue = PriorityQueue<std::string>;
  using Instruction = std::function<void(Queue&)>;

public:

  static Instruction interpret(std::string command);

private:

  enum class TokenType
  {
    Add, Get, Accelerate, LowPriority, NormalPriority, HighPriority, StringLiteral
  };

  struct token_t
  {
    TokenType type;
    std::string lexeme;
  };

  using Tokens = std::list<token_t>;

  static Tokens scan_(std::string&);
  static Instruction parse_(std::list<token_t>);

  static std::string extract_next_lexeme_(std::string&);

  static Instruction parse_add_(std::list<token_t>&);
  static Instruction parse_get_(std::list<token_t>&);
  static Instruction parse_accelerate_(std::list<token_t>&);

  static const std::unordered_map<std::string, TokenType> keywords_;
  static const Instruction invalid_instruction_;
};

#endif // QUEUE_INTERPRETER_HPP
