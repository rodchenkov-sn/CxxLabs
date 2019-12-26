#include <iostream>
#include <memory>

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

int main()
{
  try {
    rodchenkov::CompositeShape cs{};
    cs.add(rodchenkov::Rectangle{{10, 10}, 10, 10});
    cs.add(rodchenkov::Circle{{15, 15}, 5});
    cs.printData(std::cout);
    cs[1].scale(2);
    cs.printData(std::cout);
    cs.remove(1);
    cs.printData(std::cout);
  } catch (const std::invalid_argument& exc) {
    std::cerr << "error: invalid parameter \"" << exc.what() << "\"" << std::endl;
    return 1;
  } catch (const std::exception& exc) {
    std::cerr << "error: " << exc.what() << std::endl;
    return 2;
  }
  return 0;
}
