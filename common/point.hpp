#ifndef POINT_HPP
#define POINT_HPP

#include <ostream>

struct point_t
{
  static const std::string PRINT_FMT;

  int x;
  int y;
};

std::ostream& operator << (std::ostream&, const point_t&);
std::istream& operator >> (std::istream&, point_t&);

#endif // POINT_HPP
