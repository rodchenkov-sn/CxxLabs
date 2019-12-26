#include "rectangle.hpp"

#include <stdexcept>

Rectangle::Rectangle(const point_t& pos, const double height, const double width) :
    height_(height),
    width_(width),
    frame_rect_({height, width, pos})
{
  if ((height < 0) || (width < 0)) {
    throw std::invalid_argument("rectangle width and height can\'t be negative");
  }
}

double Rectangle::getArea() const noexcept
{
  return height_ * width_;
}

rectangle_t Rectangle::getFrameRect() const noexcept
{
  return frame_rect_;
}

void Rectangle::printData(std::ostream& stream) const
{
  stream << "Shape : Rectangle\n"
      << "Position : (" <<  frame_rect_.pos.x << ", " << frame_rect_.pos.y <<")\n"
      << "Width : " << width_ << "\n"
      << "Height : " << height_ << "\n"
      << "Area : " << getArea() << "\n"; 
}

void Rectangle::move(const point_t& point) noexcept
{
  frame_rect_.pos = point;
}

void Rectangle::move(const double dx, const double dy) noexcept
{
  frame_rect_.pos.x += dx;
  frame_rect_.pos.y += dy;
}
