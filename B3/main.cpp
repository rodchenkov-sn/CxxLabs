#include <iostream>

#include "tasks.hpp"
#include <string>

int main(int argc, char* argv[])
{
  try {
    if (argc != 2) {
      throw std::invalid_argument{ "usage: > Lab3 task_id" };
    }
    const int taskId = std::stoi(argv[1]);
    switch (taskId) {
    case 1: 
      task1(); 
      break;
    case 2: 
      task2();
      break;
    default:
      throw std::invalid_argument{ "invalid task_id" };
    }
    return 0;
  } catch (const std::invalid_argument& exc) {
    std::cerr << exc.what() << "\n";
    return 1;
  } catch (const std::exception& exc) {
    std::cerr << exc.what() << "\n";
    return 2;
  }
}
