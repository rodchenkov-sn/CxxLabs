#include "circle.hpp"

#include <stdexcept>
#include <cmath>

const double PI = atan(1) * 4;

Circle::Circle(const point_t& pos, const double radius) :
    radius_(radius),
    frame_rect_({radius * 2, radius * 2, pos})
{
  if (radius < 0) {
    throw std::invalid_argument("circle radius can\'t be negative");
  }
}

double Circle::getArea() const noexcept
{
  return pow(radius_, 2) * PI;
}

rectangle_t Circle::getFrameRect() const noexcept
{
  return frame_rect_;
}

void Circle::printData(std::ostream& stream) const
{
  stream << "Shape : Circle\n"
      << "Position : (" <<  frame_rect_.pos.x << ", " << frame_rect_.pos.y <<")\n"
      << "Raius : " << radius_ << "\n"
      << "Area : " << getArea() << "\n"; 
}

void Circle::move(const point_t& point) noexcept
{
  frame_rect_.pos = point;
}

void Circle::move(const double dx, const double dy) noexcept
{
  frame_rect_.pos.x += dx;
  frame_rect_.pos.y += dy;
}
