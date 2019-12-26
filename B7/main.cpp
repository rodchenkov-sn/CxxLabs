#include <iostream>
#include <string>

#include "tasks.hpp"

int main(int argc, char* argv[])
{
  try {
    if (argc != 2) {
      throw std::invalid_argument{ "Usage: > Lab7 task_id" };
    }

    int taskId = std::stoi(argv[1]);
    switch (taskId) {
    case 1:
      task1();
      break;
    case 2:
      task2();
      break;
    default:
      throw std::invalid_argument{ "Unexpected task_id" };
    }

    return 0;
  } catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
