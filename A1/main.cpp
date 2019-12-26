#include <iostream>
#include <memory>

#include "rectangle.hpp"
#include "circle.hpp"

void testShape(const std::unique_ptr<Shape>& s, const point_t& p);

int main()
{
  try {
    std::unique_ptr<Shape> shapes[2];
    shapes[0] = std::make_unique<Rectangle>(point_t{10, 10}, 20, 40);
    shapes[1] = std::make_unique<Circle>(point_t{100, 100}, 10);
    for (auto& sh : shapes) {
      testShape(sh, {5, 5});
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

void testShape(const std::unique_ptr<Shape>& s, const point_t& p)
{
  std::cout << "Before moving :\n";
  s->printData(std::cout);
  s->move(p);
  std::cout << "After moving to (" << p.x << ", " << p.y << ") :\n";
  s->printData(std::cout);
}
