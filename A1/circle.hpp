#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(const point_t&, double);

  double      getArea() const noexcept override;
  rectangle_t getFrameRect() const noexcept override;
  void        printData(std::ostream&) const override;
  void        move(const point_t&) noexcept override;
  void        move(double, double) noexcept override;

private:
  double      radius_;
  rectangle_t frame_rect_;
};

#endif // CIRCLE_HPP
