#include <iostream>

#include <vector>
#include <iterator>
#include <algorithm>

#include "dataStruct.hpp"

int main(int argc, char*[])
{
  try {
    if (argc == 1) {
      std::vector<DataStruct> dataStructs(std::istream_iterator<DataStruct>{ std::cin }, std::istream_iterator<DataStruct>{});
      if (!std::cin.eof() && std::cin.fail()) {
        throw std::ios_base::failure{ "input failure" };
      }
      std::sort(dataStructs.begin(), dataStructs.end());
      std::copy(dataStructs.begin(), dataStructs.end(), std::ostream_iterator<DataStruct>{ std::cout, "\n" });
    } else {
      throw std::invalid_argument{ "usage: > Lab4" };
    }
    return 0;
  } catch (const std::invalid_argument& e) {
    std::cerr << e.what() << "\n";
    return 1;
  } catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    return 2;
  }
}
