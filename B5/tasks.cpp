#include "tasks.hpp"

#include <string>
#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <vector>
#include <tuple>
#include <iterator>
#include <numeric>

#include "shape.hpp"

void task1()
{
  std::unordered_set<std::string> words{ std::istream_iterator<std::string>{ std::cin }, std::istream_iterator<std::string>{} };
  if (!std::cin.eof()) {
    throw std::ios_base::failure{ "input failure" };
  }
  std::copy(words.begin(), words.end(), std::ostream_iterator<std::string>{ std::cout, "\n" });
}

void task2()
{
  // 1

  std::vector<Shape> shapes{ std::istream_iterator<Shape>{ std::cin }, std::istream_iterator<Shape>{} };
  if (!std::cin.eof()) {
    throw std::runtime_error{ "invalid input" };
  }

  // 2

  auto vertices = std::accumulate(shapes.cbegin(), shapes.cend(), 0, [](size_t v, const Shape& s) { return v + s.size(); });
  std::cout << "Vertices: " << vertices << "\n";

  // 3

  auto shapesCount = std::accumulate(shapes.begin(), shapes.end(),
    std::make_tuple(0, 0, 0), [](const std::tuple<size_t, size_t, size_t>& t, const Shape& s) {
      if (s.size() == 3)  return std::make_tuple(std::get<0>(t) + 1, std::get<1>(t), std::get<2>(t));
      if (isSquare(s))    return std::make_tuple(std::get<0>(t), std::get<1>(t) + 1, std::get<2>(t) + 1);
      if (isRectangle(s)) return std::make_tuple(std::get<0>(t), std::get<1>(t), std::get<2>(t) + 1);
      return t;
    });
  std::cout << "Triangles: " << std::get<0>(shapesCount) << "\n"
            << "Squares: " << std::get<1>(shapesCount) << "\n"
            << "Rectangles: " << std::get<2>(shapesCount) << "\n";

  // 4

  shapes.erase(std::remove_if(shapes.begin(), shapes.end(), [](const Shape& s) { return s.size() == 5; }), shapes.end());

  // 5

  std::vector<point_t> points(shapes.size());
  std::transform(shapes.begin(), shapes.end(), points.begin(), [](const Shape& s) { return s[0]; });
  std::cout << "Points: ";
  std::copy(points.begin(), points.end(), std::ostream_iterator<point_t>{ std::cout, " " });
  std::cout << "\n";

  // 6

  auto trianglesBound = std::partition(shapes.begin(), shapes.end(), [](const Shape& s) { return s.size() == 3; });
  auto squaresBound   = std::partition(trianglesBound, shapes.end(), [](const Shape& s) { return isSquare(s); });
  std::partition(squaresBound, shapes.end(), [](const Shape& s) { return isRectangle(s); });

  // 7

  std::cout << "Shapes:\n";
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape>{ std::cout, "\n" });

}
