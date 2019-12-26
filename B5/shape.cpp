#include "shape.hpp"

#include <iterator>

#include "ioUtils.hpp"

std::ostream& operator<<(std::ostream& stream, const Shape& shape)
{
  std::ostream::sentry sentry{ stream };
  if (!sentry) {
    return stream;
  }
  stream << shape.size() << " ";
  std::copy(shape.begin(), shape.end(), std::ostream_iterator<point_t>{ stream, " " });
  return stream;
}

std::istream& operator>>(std::istream& stream, Shape& shape)
{
  size_t size;
  std::istream::sentry sentry{ stream };
  if (!sentry) {
    return stream;
  }
  FlagGuard flagGuard{ stream };
  stream >> std::noskipws >> ws >> size;
  if (!stream.fail()) {
    Shape tmp(size);
    for (auto& s : tmp) {
      stream >> s;
    }
    if (!stream.fail()) {
      shape = std::move(tmp);
    }
  }
  return stream;
}

bool isSquare(const Shape& shape)
{
  if (!isRectangle(shape)) {
    return false;
  }

  std::pair<int, int> diag1 = { (shape[0].x - shape[2].x), (shape[0].y - shape[2].y) };
  std::pair<int, int> diag2 = { (shape[1].x - shape[3].x), (shape[1].y - shape[3].y) };

  return (diag1.first * diag2.first + diag1.second * diag2.second) == 0;
}

bool isRectangle(const Shape& shape)
{
  if (shape.size() != 4) {
    return false;
  }

  std::pair<int, int> side1 = { (shape[0].x - shape[1].x), (shape[0].y - shape[1].y) };
  std::pair<int, int> side2 = { (shape[0].x - shape[3].x), (shape[0].y - shape[3].y) };

  return (side1.first * side2.first + side1.second * side2.second) == 0;
}
