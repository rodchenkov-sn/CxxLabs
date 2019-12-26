#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(const point_t&, double, double);

  double      getArea() const noexcept override;
  rectangle_t getFrameRect() const noexcept override;
  void        printData(std::ostream&) const override;
  void        move(const point_t&) noexcept override;
  void        move(double, double) noexcept override;

private:
  double      height_;
  double      width_;
  rectangle_t frame_rect_;
};

#endif // RECTANGLE_HPP
