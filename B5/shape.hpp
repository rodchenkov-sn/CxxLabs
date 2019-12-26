#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <ostream>
#include <vector>

#include "point.hpp"

using Shape = std::vector<point_t>;
std::ostream& operator << (std::ostream&, const Shape&);
std::istream& operator >> (std::istream&, Shape&);

bool isSquare(const Shape&);
bool isRectangle(const Shape&);

#endif // SHAPE_HPP
