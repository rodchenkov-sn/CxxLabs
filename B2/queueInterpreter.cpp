#include "queueInterpreter.hpp"

#include <stdexcept>
#include <iostream>

const std::unordered_map<std::string, QueueInterpreter::TokenType> QueueInterpreter::keywords_ = {
    { "get"       , TokenType::Get            },
    { "add"       , TokenType::Add            },
    { "accelerate", TokenType::Accelerate     },
    { "low"       , TokenType::LowPriority    },
    { "normal"    , TokenType::NormalPriority },
    { "high"      , TokenType::HighPriority   }
};

const QueueInterpreter::Instruction QueueInterpreter::invalid_instruction_ = [](Queue&) { std::cout << "<INVALID COMMAND>\n"; };

QueueInterpreter::Instruction QueueInterpreter::interpret(std::string command)
{
  if (command.empty()) {
    return [](Queue&) {};
  }
  return parse_(scan_(command));
}


QueueInterpreter::Tokens QueueInterpreter::scan_(std::string& command)
{
  Tokens tokenSeq;
  while (!command.empty()) {
    auto curr = extract_next_lexeme_(command);
    if (keywords_.find(curr) != keywords_.end()) {
      const auto tokenT = keywords_.at(curr);
      if (tokenT == TokenType::HighPriority || tokenT == TokenType::NormalPriority || tokenT == TokenType::LowPriority) {
        tokenSeq.push_back({ tokenT, curr });
        tokenSeq.push_back({ TokenType::StringLiteral, command });
        return tokenSeq;
      }
      tokenSeq.push_back({ tokenT, curr });
    } else {
      tokenSeq.push_back({ TokenType::StringLiteral, curr });
    }
  }
  return tokenSeq;
}

QueueInterpreter::Instruction QueueInterpreter::parse_(Tokens tokenSeq)
{
  switch (tokenSeq.front().type) {
  case TokenType::Add:        return parse_add_(tokenSeq);
  case TokenType::Get:        return parse_get_(tokenSeq);
  case TokenType::Accelerate: return parse_accelerate_(tokenSeq);

  case TokenType::LowPriority:
  case TokenType::NormalPriority:
  case TokenType::HighPriority:
  case TokenType::StringLiteral:
  default:
    return invalid_instruction_;
  }
}

std::string QueueInterpreter::extract_next_lexeme_(std::string& sentence)
{
  if (sentence.empty()) {
    return "";
  }
  if (sentence.find(' ') == std::string::npos) {
    auto word = sentence;
    sentence = "";
    return word;
  }
  const auto wordLength = sentence.find(' ');
  size_t trimLength = wordLength;
  while (isspace(sentence[trimLength])) {
    ++trimLength;
  }
  auto word = sentence.substr(0, wordLength);
  sentence.erase(0, trimLength);
  return word;
}

QueueInterpreter::Instruction QueueInterpreter::parse_add_(Tokens& tokenSeq)
{
  if (tokenSeq.size() == 3) {
    tokenSeq.pop_front();
    auto priority = Queue::low();
    if (tokenSeq.front().type == TokenType::HighPriority) {
      priority = Queue::high();
    } else if (tokenSeq.front().type == TokenType::NormalPriority) {
      priority = Queue::normal();
    } else if (tokenSeq.front().type != TokenType::LowPriority) {
      return invalid_instruction_;
    }
    tokenSeq.pop_front();
    if (tokenSeq.front().type == TokenType::StringLiteral && !tokenSeq.front().lexeme.empty()) {
      return [=](Queue& queue) {
        queue.put(tokenSeq.front().lexeme, priority);
      };
    }
  }
  return invalid_instruction_;
}

QueueInterpreter::Instruction QueueInterpreter::parse_get_(Tokens& tokenSeq)
{
  if (tokenSeq.size() == 1) {
    return [](Queue& queue) {
      if (queue.empty()) {
        std::cout << "<EMPTY>\n";
      }
      else {
        queue.applyFront([](const std::string& str) {
          std::cout << str << "\n";
          });
      }
    };
  }
  return invalid_instruction_;
}

QueueInterpreter::Instruction QueueInterpreter::parse_accelerate_(Tokens& tokenSeq)
{
  if (tokenSeq.size() == 1) {
    return [](Queue& queue) {
      queue.accelerate();
    };
  }
  return invalid_instruction_;
}
