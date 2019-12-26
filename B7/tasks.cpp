#include "tasks.hpp"

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>

#include "shapes.hpp"

void task1()
{
  std::transform(
    std::istream_iterator<double>{std::cin},
    std::istream_iterator<double>{},
    std::ostream_iterator<double>{ std::cout, " " },
    std::bind1st(std::multiplies<double>{}, M_PI)
  );
  if (!std::cin.eof()) {
    throw std::ios_base::failure{ "input failure" };
  }
}

void task2()
{
  std::vector<Shape::ShPtr> shapes{ std::istream_iterator<Shape::ShPtr>{ std::cin }, std::istream_iterator<Shape::ShPtr>{} };
  if (!std::cin.eof()) {
    throw std::ios_base::failure{ "input failure" };
  }

  std::cout << "Original:\n";
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape::ShPtr>{ std::cout, "\n" });
  std::cout << "Left-Right:\n";

  std::sort(shapes.begin(), shapes.end(), std::bind(
    &Shape::isMoreLeft, std::placeholders::_1, std::placeholders::_2
  ));
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape::ShPtr>{ std::cout, "\n" });
  std::cout << "Right-Left:\n";
  std::sort(shapes.begin(), shapes.end(), std::bind(
    &Shape::isMoreLeft, std::placeholders::_2, std::placeholders::_1
  ));
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape::ShPtr>{ std::cout, "\n" });
  std::cout << "Top-Bottom:\n";
  std::sort(shapes.begin(), shapes.end(), std::bind(
    &Shape::isUpper, std::placeholders::_1, std::placeholders::_2
  ));
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape::ShPtr>{ std::cout, "\n" });
  std::cout << "Bottom-Top:\n";
  std::sort(shapes.begin(), shapes.end(), std::bind(
    &Shape::isUpper, std::placeholders::_2, std::placeholders::_1
  ));
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape::ShPtr>{ std::cout, "\n" });
}
