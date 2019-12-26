#include <iostream>
#include "rectangle.hpp"
#include "matrix.hpp"
#include "split.hpp"

int main()
{
  try {

    rodchenkov::SharedShapeArray shapes = std::make_unique<std::shared_ptr<rodchenkov::Shape>[]>(6);
    shapes[0] = std::make_shared<rodchenkov::Rectangle>(rodchenkov::Rectangle{ { 0  , 0 }, 10, 10 });
    shapes[1] = std::make_shared<rodchenkov::Rectangle>(rodchenkov::Rectangle{ { 20 , 0 }, 10, 10 });
    shapes[2] = std::make_shared<rodchenkov::Rectangle>(rodchenkov::Rectangle{ { 0  , 0 }, 10, 10 });
    shapes[3] = std::make_shared<rodchenkov::Rectangle>(rodchenkov::Rectangle{ { 20 , 0 }, 10, 10 });
    shapes[4] = std::make_shared<rodchenkov::Rectangle>(rodchenkov::Rectangle{ { -20, 0 }, 10, 10 });
    shapes[5] = std::make_shared<rodchenkov::Rectangle>(rodchenkov::Rectangle{ { 0  , 0 }, 5 , 5 });

    rodchenkov::Matrix<std::shared_ptr<rodchenkov::Shape>> splited = rodchenkov::splitIntoLayers(shapes, 6);

    std::cout << splited.rows() << " " << splited.cols() << "\n";

    splited.forEachSafe([](std::shared_ptr<rodchenkov::Shape>& s) { s->printData(std::cout); });

  }
  catch (const std::invalid_argument& exc) {
    std::cerr << exc.what() << std::endl;
    return 1;
  }
  catch (const std::exception& exc) {
    std::cerr << exc.what() << std::endl;
    return 2;
  }
  return 0;
}
