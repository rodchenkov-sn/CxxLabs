#include "rectangle.hpp"

#include <stdexcept>
#include <cmath>

rodchenkov::Rectangle::Rectangle(const point_t& pos, const double height, const double width) :
  height_(height),
  width_(width),
  rotation_(0),
  frame_rect_({ height, width, pos })
{
  if ((height < 0) || (width < 0)) {
    throw std::invalid_argument("rectangle width and height can\'t be negative");
  }
}

rodchenkov::Rectangle::Rectangle(const point_t& pos, const double height, const double width, const double rotation) :
  height_(height),
  width_(width),
  rotation_(rotation),
  frame_rect_({ height, width, pos })
{
  if ((height < 0) || (width < 0)) {
    throw std::invalid_argument("rectangle width and height can\'t be negative");
  }
  rotation_ = rotation_ > 0 ? fmod(rotation_, 2 * M_PI) : 2 * M_PI + fmod(rotation_, 2 * M_PI);
  computeFrame();
}

double rodchenkov::Rectangle::getArea() const noexcept
{
  return height_ * width_;
}

double rodchenkov::Rectangle::getRotation() const noexcept
{
  return rotation_;
}

rodchenkov::rectangle_t rodchenkov::Rectangle::getFrameRect() const noexcept
{
  return frame_rect_;
}

void rodchenkov::Rectangle::printData(std::ostream& stream) const
{
  stream << "Shape : Rectangle\n"
      << "Position : (" << frame_rect_.pos.x << ", " << frame_rect_.pos.y << ")\n"
      << "Width : " << width_ << "\n"
      << "Height : " << height_ << "\n"
      << "Area : " << getArea() << "\n"
      << "Rotation : " << rotation_ << "\n"
      << "Framing rectangle (h x w) : " << frame_rect_.height << " x " << frame_rect_.width << "\n";
}

void rodchenkov::Rectangle::move(const point_t& point) noexcept
{
  frame_rect_.pos = point;
}

void rodchenkov::Rectangle::move(const double dx, const double dy) noexcept
{
  frame_rect_.pos.x += dx;
  frame_rect_.pos.y += dy;
}

using namespace rodchenkov;

void Rectangle::setRotation(const double rotation) noexcept
{
  rotation_ = rotation;
  rotation_ = rotation_ > 0 ? fmod(rotation_, 2 * M_PI) : 2 * M_PI + fmod(rotation_, 2 * M_PI);
  computeFrame();
}

void rodchenkov::Rectangle::rotate(const double rotation) noexcept
{
  rotation_ += rotation;
  rotation_ = rotation_ > 0 ? fmod(rotation_, 2 * M_PI) : 2 * M_PI + fmod(rotation_, 2 * M_PI);
  computeFrame();
}

void rodchenkov::Rectangle::scale(const double ratio)
{
  if (ratio < 0) {
    throw std::invalid_argument("scaling ratio can\'t be negative");
  }
  width_             *= ratio;
  height_            *= ratio;
  frame_rect_.width  *= ratio;
  frame_rect_.height *= ratio;
}

double rodchenkov::Rectangle::getWidth() const noexcept
{
  return width_;
}

double rodchenkov::Rectangle::getHeight() const noexcept
{
  return height_;
}

void rodchenkov::Rectangle::computeFrame() noexcept
{
  frame_rect_.height = width_ * fabs(sin(rotation_)) + height_ * fabs(cos(rotation_));
  frame_rect_.width  = width_ * fabs(cos(rotation_)) + height_ * fabs(sin(rotation_));
}

std::unique_ptr<rodchenkov::Shape> rodchenkov::Rectangle::clone() const
{
  return std::make_unique<Rectangle>(*this);
}
