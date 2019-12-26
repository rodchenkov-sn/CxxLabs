#include <iostream>
#include <string>
#include "tasks.hpp"

int main(int argc, char* argv[])
{
  try {
    if (argc > 1) {
      const int taskId = std::stoi(argv[1]);
      switch (taskId) {
      case 1:
        if (argc == 3) {
          task1(argv[2]);
          break;
        }
        throw std::invalid_argument{ "usage: > lab1 1 (ascending|descending)" };
      case 2:
        if (argc == 3) {
          task2(argv[2]);
          break;
        }
        throw std::invalid_argument{ "usage: > lab1 2 file_path" };
      case 3:
        if (argc == 2) {
          task3();
          break;
        }
        throw std::invalid_argument{ "usage: > lab1 3" };
      case 4:
        if (argc == 4) {
          task4(argv[2], argv[3]);
          break;
        }
        throw std::invalid_argument{ "usage: > lab1 4 (ascending|descending) vector_size" };
      default:
        throw std::invalid_argument{ "invalid task id" };
      }
    } else {
      throw std::invalid_argument{ "usage: > lab1 task_id [task_args]" };
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
