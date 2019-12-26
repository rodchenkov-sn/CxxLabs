#include <iostream>
#include <algorithm>
#include <iterator>

#include "statFunctor.hpp"

int main(int argc, char*[])
{
  try {

    if (argc != 1) {
      throw std::invalid_argument{ "Usage: > Lab6" };
    }

    const auto statFunctor = std::for_each(std::istream_iterator<int>{ std::cin }, std::istream_iterator<int>{}, StatFunctor{});
    if (!std::cin.eof()) {
      throw std::ios_base::failure{ "input failure" };
    }

    std::cout << statFunctor << "\n";

    return 0;
  } catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
}

