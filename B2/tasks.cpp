#include "tasks.hpp"

#include <list>
#include <iostream>
#include <sstream>

#include "queueInterpreter.hpp"

void task1()
{
  PriorityQueue<std::string> priorityQueue;
  std::string cmd;
  while (!std::cin.eof()) {
    std::getline(std::cin, cmd);
    QueueInterpreter::interpret(cmd)(priorityQueue);
  }
}

void task2()
{
  std::list<int> seq;
  int curr;
  while (std::cin >> curr, !std::cin.eof()) {
    if (std::cin.fail()) {
      throw std::runtime_error{ "in task #2 expected integer sequence" };
    }
    if (curr < 1 || curr > 20) {
      throw std::runtime_error{ "in task #2 expected sequence of integers in range 1 .. 20" };
    }
    seq.push_back(curr);
  }
  if (seq.size() > 20) {
    throw std::runtime_error{ "in task #2 expected sequence length in range 0 .. 20" };
  }
  auto b = seq.begin();
  auto e = seq.end();
  while (b != e) {
    std::cout << *b;
    ++b;
    if (b == e) {
      break;
    }
    std::cout << " " << *(--e);
    if (b != e) {
      std::cout << " ";
    }
  }
  std::cout << "\n";
}
