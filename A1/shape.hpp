#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <ostream>

#include "base-types.hpp"

class Shape
{
public:
  virtual ~Shape() = default;

  virtual double      getArea() const noexcept = 0;
  virtual rectangle_t getFrameRect() const noexcept = 0;
  virtual void        printData(std::ostream&) const = 0;
  virtual void        move(const point_t&) noexcept = 0;
  virtual void        move(double, double) noexcept = 0;
};

#endif // SHAPE_HPP
