#include <iostream>
#include <string>

#include "tasks.hpp"

int main(int argc, char* argv[])
{
  try {
    if (argc == 2) {
      const int taskId = std::stoi(argv[1]);
      switch (taskId) {
      case 1:
        task1();
        break;
      case 2:
        task2();
        break;
      default:
        throw std::invalid_argument{ "invalid task id" };
      }
    } else {
      throw std::invalid_argument{ "usage: > Lab2 task_id" };
    }
    return 0;
  } catch (const std::invalid_argument& exc) {
    std::cerr << "Invalid argument: " << exc.what() << "\n";
    return 1;
  } catch (const std::exception& exc) {
    std::cerr << exc.what() << "\n";
    return 2;
  }
}
