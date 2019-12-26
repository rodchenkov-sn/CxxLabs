#include "tasks.hpp"

#include <iostream>
#include <algorithm>

#include "phoneBookInterpreter.hpp"
#include "phoneBookInterface.hpp"
#include "factStream.hpp"

void task1()
{
  PhoneBookInterface phoneBookInterface;
  std::string cmd;
  while (!std::cin.eof()) {
    std::getline(std::cin, cmd);
    std::cout << PhoneBookInterpreter::interpret(cmd)(phoneBookInterface);
  }
}

void task2()
{
  const FactStream fs{ 10_uc };
  std::copy(fs.begin(), fs.end(), std::ostream_iterator<unsigned long long>{ std::cout, " " });
  std::cout << "\n";
  std::copy(fs.rbegin(), fs.rend(), std::ostream_iterator<unsigned long long>{ std::cout, " " });
  std::cout << "\n";
}
