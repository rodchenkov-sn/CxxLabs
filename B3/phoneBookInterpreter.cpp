#include "phoneBookInterpreter.hpp"

#include <algorithm>
#include <stdexcept>

#include "phoneBookInterface.hpp"

const PhoneBookInterpreter::Instruction PhoneBookInterpreter::invalidInstruction = [](PhoneBookInterface&) {
  return "<INVALID COMMAND>\n";
};

const std::unordered_map<std::string, std::function<PhoneBookInterpreter::Instruction(std::string&)>> PhoneBookInterpreter::parsers = {
  { "add"   , &PhoneBookInterpreter::parse_add_    },
  { "store" , &PhoneBookInterpreter::parse_store_  },
  { "insert", &PhoneBookInterpreter::parse_insert_ },
  { "delete", &PhoneBookInterpreter::parse_delete_ },
  { "show"  , &PhoneBookInterpreter::parse_show_   },
  { "move"  , &PhoneBookInterpreter::parse_move_   }
};

PhoneBookInterpreter::Instruction PhoneBookInterpreter::interpret(const std::string& cmd)
{
  if (cmd.empty()) {
    return [](PhoneBookInterface&) { return ""; };
  }
  try {
    return parse_(cmd);
  } catch (...) {
    return invalidInstruction;
  }
}

PhoneBookInterpreter::Instruction PhoneBookInterpreter::parse_(std::string cmd)
{
  const std::string command = extract_lexeme_(cmd);
  const auto parser = parsers.find(command);
  if (parser == parsers.end()) {
    return invalidInstruction;
  }
  return parser->second(cmd);
}

PhoneBookInterpreter::Instruction PhoneBookInterpreter::parse_add_(std::string& args)
{
  const auto phone = extract_lexeme_(args);
  if (phone.empty()) {
    return invalidInstruction;
  }
  char* end = nullptr;
  (void)strtoll(phone.c_str(), &end, 10);
  if (*end) {
    return invalidInstruction;
  }
  if (args.empty() || args[0] != '\"') {
    return invalidInstruction;
  }
  const auto name = extract_str_(args);
  if (!args.empty()) {
    return invalidInstruction;
  }
  return [phone, name](PhoneBookInterface& p) {
    p.add(phone, name);
    return "";
  };
}

PhoneBookInterpreter::Instruction PhoneBookInterpreter::parse_insert_(std::string& args)
{
  const auto position = extract_lexeme_(args);
  const auto bookmark = extract_lexeme_(args);
  const auto phone = extract_lexeme_(args);
  if (args.empty() || args[0] != '\"') {
    return invalidInstruction;
  }
  const auto name = extract_str_(args);
  if (position.empty() || bookmark.empty() || phone.empty() || !args.empty()) {
    return invalidInstruction;
  }
  char* end = nullptr;
  (void)strtoll(phone.c_str(), &end, 10);
  if (*end) {
    return invalidInstruction;
  }
  if (position == "before") {
    return [bookmark, phone, name](PhoneBookInterface& p) {
      return p.insertBefore(bookmark, phone, name);
    };
  }
  if (position == "after") {
    return [bookmark, phone, name](PhoneBookInterface& p) {
      return p.insertAfter(bookmark, phone, name);
    };
  }
  return invalidInstruction;
}

PhoneBookInterpreter::Instruction PhoneBookInterpreter::parse_delete_(std::string& args)
{
  const auto bookmark = extract_lexeme_(args);
  if (bookmark.empty() || !args.empty()) {
    return invalidInstruction;
  }
  return [bookmark](PhoneBookInterface& p) {
    return p.remove(bookmark);
  };
}

PhoneBookInterpreter::Instruction PhoneBookInterpreter::parse_show_(std::string& args)
{
  const auto bookmark = extract_lexeme_(args);
  if (bookmark.empty() || !args.empty()) {
    return invalidInstruction;
  }
  return [bookmark](PhoneBookInterface& p) {
    return p.show(bookmark);
  };
}

PhoneBookInterpreter::Instruction PhoneBookInterpreter::parse_move_(std::string& args)
{
  const auto bookmark = extract_lexeme_(args);
  const auto step = extract_lexeme_(args);
  if (bookmark.empty() || step.empty() || !args.empty()) {
    return invalidInstruction;
  }
  if (step == "first") {
    return [bookmark](PhoneBookInterface& p) {
      return p.moveToFirst(bookmark);
    };
  }
  if (step == "last") {
    return [bookmark](PhoneBookInterface& p) {
      return p.moveToLast(bookmark);
    };
  }
  char* end = nullptr;
  auto s = strtoll(step.c_str(), &end, 10);
  if (*end) {
    return [](PhoneBookInterface&) { return "<INVALID STEP>\n"; };
  }
  return [bookmark, s](PhoneBookInterface& p) {
    return p.advance(bookmark, s);
  };
}

PhoneBookInterpreter::Instruction PhoneBookInterpreter::parse_store_(std::string& args)
{
  const auto oldBM = extract_lexeme_(args);
  const auto newBM = extract_lexeme_(args);
  if (oldBM.empty() || newBM.empty() || !args.empty()) {
    return invalidInstruction;
  }
  return [oldBM, newBM](PhoneBookInterface& p) {
    return p.storeBm(oldBM, newBM);
  };
}

std::string PhoneBookInterpreter::extract_str_(std::string& sentence)
{
  size_t pos = 1;
  std::string str;
  while (pos < sentence.length() && sentence[pos] != '\"') {
    if (sentence[pos] == '\\' && pos + 1 < sentence.length() && sentence[pos + 1] == '\"') {
      pos += 2;
    } else {
      pos += 1;
    }
  }
  if (pos == sentence.length()) {
    throw std::runtime_error{ "unterminated string" };
  }
  str += sentence.substr(1, pos - 1);
  str.erase(std::remove(str.begin(), str.end(), '\\'), str.end());
  ++pos;
  while (pos < sentence.length() && isspace(sentence[pos])) {
    ++pos;
  }
  sentence.erase(0, pos);
  return str;
}

std::string PhoneBookInterpreter::extract_lexeme_(std::string& sentence)
{
  if (sentence.empty()) {
    return "";
  }
  const auto space = std::find_if(sentence.begin(), sentence.end(), [](const char& c) {return isspace(c); });
  if (space == sentence.end()) {
    auto word = sentence;
    sentence = "";
    return word;
  }
  const auto wordLength = std::distance(sentence.begin(), space);
  size_t trimLength = wordLength;
  while (isspace(sentence[trimLength])) {
    ++trimLength;
  }
  auto word = sentence.substr(0, wordLength);
  sentence.erase(0, trimLength);
  return word;

}
