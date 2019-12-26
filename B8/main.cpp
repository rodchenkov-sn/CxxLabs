#include <iostream>
#include <cstring>
#include <algorithm>
#include <functional>

#include "tokenInputIterator.hpp"
#include "tokenValidator.hpp"
#include "tokenOutputIterator.hpp"

int main(int argc, char* argv[])
{
  try {
    size_t width = 40;
    switch (argc) {
    case 1:
      break;
    case 3:
      if (strcmp("--line-width", argv[1]) == 0) {
        width = std::stoi(argv[2]);
        break;
      }
    default:
      throw std::invalid_argument{ "Usage: > Lab8 (--line-width line_width)?" };
    }

    TokenValidator tv;

    std::transform(
      TokenInputIterator{ std::cin }, 
      TokenInputIterator{}, 
      TokenOutputIterator{ std::cout, width },
      std::ref(tv)
    );

    if (!tv.status().ok) {
      std::cerr << tv.status();
      return 1;
    }

    return 0;
  }
  catch (const std::exception & e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
