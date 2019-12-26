#include "circle.hpp"

#include <stdexcept>

#define _USE_MATH_DEFINES
#include <math.h>

rodchenkov::Circle::Circle(const point_t& pos, const double radius) :
  radius_(radius),
  frame_rect_({ radius * 2, radius * 2, pos })
{
  if (radius < 0) {
    throw std::invalid_argument("circle radius can\'t be negative");
  }
}

double rodchenkov::Circle::getArea() const noexcept
{
  return pow(radius_, 2) * M_PI;
}

double rodchenkov::Circle::getRotation() const noexcept
{
  return 0;
}

rodchenkov::rectangle_t rodchenkov::Circle::getFrameRect() const noexcept
{
  return frame_rect_;
}

void rodchenkov::Circle::printData(std::ostream& stream) const
{
  stream << "Shape : Circle\n"
      << "Position : (" << frame_rect_.pos.x << ", " << frame_rect_.pos.y << ")\n"
      << "Radius : " << radius_ << "\n"
      << "Area : " << getArea() << "\n"
      << "Framing rectangle (h x w) : " << frame_rect_.height << " x " << frame_rect_.width << "\n";
}

void rodchenkov::Circle::move(const point_t& point) noexcept
{
  frame_rect_.pos = point;
}

void rodchenkov::Circle::move(const double dx, const double dy) noexcept
{
  frame_rect_.pos.x += dx;
  frame_rect_.pos.y += dy;
}

void rodchenkov::Circle::setRotation(double) noexcept
{
}

void rodchenkov::Circle::rotate(double) noexcept
{
}

void rodchenkov::Circle::scale(const double ratio)
{
  if (ratio < 0) {
    throw std::invalid_argument("scaling ratio can\'t be negative");
  }
  radius_            *= ratio;
  frame_rect_.width  *= ratio;
  frame_rect_.height *= ratio;
}

double rodchenkov::Circle::getRadius() const noexcept
{
  return radius_;
}

std::unique_ptr<rodchenkov::Shape> rodchenkov::Circle::clone() const
{
  return std::make_unique<Circle>(*this);
}
