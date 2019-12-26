#include <iostream>
#include <memory>

#include "rectangle.hpp"
#include "circle.hpp"

void testShape(std::shared_ptr<rodchenkov::Shape>, const rodchenkov::point_t&, double);

int main()
{
  try {
    std::shared_ptr<rodchenkov::Shape> shapes[2];
    shapes[0] = std::make_shared<rodchenkov::Rectangle>(rodchenkov::point_t{10, 10}, 20, 40);
    shapes[1] = std::make_shared<rodchenkov::Circle>(rodchenkov::point_t{100, 100}, 10);
    for (auto& sh : shapes) {
      testShape(sh, {5, 5}, 2);
    }
  } catch (const std::invalid_argument& exc) {
    std::cerr << "error: invalid parameter \"" << exc.what() << "\"" << std::endl;
    return 1;
  } catch (const std::exception& exc) {
    std::cerr << "error: " << exc.what() << std::endl;
    return 2;
  }
  return 0;
}

void testShape(std::shared_ptr<rodchenkov::Shape> s, const rodchenkov::point_t& p, const double ratio)
{
  std::cout << "Before moving and scaling :\n";
  s->printData(std::cout);
  s->move(p);
  s->scale(ratio);
  std::cout << "After moving to (" << p.x << ", " << p.y << ") and " << ratio << " scaling :\n";
  s->printData(std::cout);
}
