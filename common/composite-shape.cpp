#include "composite-shape.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>

rodchenkov::CompositeShape::CompositeShape() :
  rotation_(0),
  count_(0),
  capacity_(0)
{
}

rodchenkov::CompositeShape::CompositeShape(const CompositeShape& cs) :
  rotation_(cs.rotation_),
  count_(cs.count_),
  capacity_(cs.capacity_),
  shapes_(std::make_unique<std::unique_ptr<Shape>[]>(capacity_))
{
  for (std::size_t i = 0; i < count_; i++) {
    shapes_[i] = cs.shapes_[i]->clone();
  }
}

rodchenkov::CompositeShape::CompositeShape(CompositeShape&& cs) noexcept
{
  swap(cs);
}

const rodchenkov::CompositeShape& rodchenkov::CompositeShape::operator=(const CompositeShape& cs)
{
  CompositeShape temp(cs);
  swap(temp);
  return *this;
}

const rodchenkov::CompositeShape& rodchenkov::CompositeShape::operator=(CompositeShape&& cs) noexcept
{
  swap(cs);
  return *this;
}

rodchenkov::Shape& rodchenkov::CompositeShape::operator [](const std::size_t n) const
{
  if (n < count_) {
    return *shapes_[n];
  }
  throw std::out_of_range{"index was out of range in CompositeShape::operator[]"};
}

double rodchenkov::CompositeShape::getArea() const noexcept
{
  double area = 0.0;
  for (std::size_t i = 0; i < count_; i++) {
    area += shapes_[i]->getArea();
  }
  return area;
}

double rodchenkov::CompositeShape::getRotation() const noexcept
{
  return rotation_;
}

rodchenkov::rectangle_t rodchenkov::CompositeShape::getFrameRect() const noexcept
{
  if (count_ > 0) {
    rectangle_t currRect = shapes_[0]->getFrameRect();
    double      left     = currRect.pos.x - currRect.width / 2;
    double      right    = currRect.pos.x + currRect.width / 2;
    double      top      = currRect.pos.y + currRect.height / 2;
    double      bottom   = currRect.pos.y - currRect.height / 2;
    for (std::size_t i = 1; i < count_; i++) {
      currRect = shapes_[i]->getFrameRect();
      double currLeft   = currRect.pos.x - currRect.width / 2;
      double currRight  = currRect.pos.x + currRect.width / 2;
      double currTop    = currRect.pos.y + currRect.height / 2;
      double currBottom = currRect.pos.y - currRect.height / 2;

      left   = std::min(currLeft, left);
      right  = std::max(currRight, right);
      top    = std::max(currTop, top);
      bottom = std::min(currBottom, bottom);
    }
    return { fabs(top - bottom), fabs(right - left), { (left + right) / 2, (top + bottom) / 2 } };
  }
  return { 0, 0, { 0, 0 } };
}

void rodchenkov::CompositeShape::printData(std::ostream& stream) const
{
  const rectangle_t frameRect = getFrameRect();
  stream << "Shape : Composite shape\n"
      << "Position : (" << frameRect.pos.x << ", " << frameRect.pos.y << ")\n"
      << "Width : " << frameRect.width << "\n"
      << "Height : " << frameRect.height << "\n"
      << "Area : " << getArea() << "\n"
      << "Number of shapes : " << count_ << "\n"
      << "Rotation : " << rotation_ << "\n";
}

void rodchenkov::CompositeShape::move(const point_t& point) noexcept
{
  const rectangle_t frameRect = getFrameRect();
  move(point.x - frameRect.pos.x, point.y - frameRect.pos.y);
}

void rodchenkov::CompositeShape::move(const double dx, const double dy) noexcept
{
  for (std::size_t i = 0; i < count_; i++) {
    shapes_[i]->move(dx, dy);
  }
}

void rodchenkov::CompositeShape::setRotation(const double rotation) noexcept
{
  rotate(rotation - rotation_);
}

void rodchenkov::CompositeShape::rotate(const double drot) noexcept
{
  rotation_ += drot;
  rotation_ = rotation_ > 0 ? fmod(rotation_, 2 * M_PI) : 2 * M_PI + fmod(rotation_, 2 * M_PI);
  rotateShapes(drot);
}

void rodchenkov::CompositeShape::scale(const double ratio)
{
  if (ratio >= 0) {
    const rectangle_t frameRect = getFrameRect();
    for (std::size_t i = 0; i < count_; i++) {
      point_t currPos   = shapes_[i]->getFrameRect().pos;
      double  relativeX = currPos.x - frameRect.pos.x;
      double  relativeY = currPos.y - frameRect.pos.y;
      double  dx        = relativeX * (ratio - 1);
      double  dy        = relativeY * (ratio - 1);
      shapes_[i]->scale(ratio);
      shapes_[i]->move(dx, dy);
    }
  } else {
    throw std::invalid_argument("scaling ratio can\'t be negative");
  }
}

void rodchenkov::CompositeShape::add(const Shape& newShape)
{
  if (count_ == capacity_) {
    resize(capacity_ + 1);
  }
  shapes_[count_++] = newShape.clone();
}

void rodchenkov::CompositeShape::remove(const std::size_t n)
{
  if (n < count_) {
    for (std::size_t i = n; i < count_ - 1; i++) {
      std::swap(shapes_[i], shapes_[i + 1]);
    }
    --count_;
    shapes_[count_].reset();
  } else {
    throw std::out_of_range{ "index was out of range in CompositeShape::remove" };
  }
}

void rodchenkov::CompositeShape::resize(const std::size_t newCapacity)
{
  if (newCapacity > capacity_) {
    ShapeArray newShapes = std::make_unique<std::unique_ptr<Shape>[]>(newCapacity);
    for (std::size_t i = 0; i < count_; i++) {
      std::swap(newShapes[i], shapes_[i]);
    }
    capacity_ = newCapacity;
    std::swap(shapes_, newShapes);
  }
}

std::size_t rodchenkov::CompositeShape::getSize() const noexcept
{
  return count_;
}

std::unique_ptr<rodchenkov::Shape> rodchenkov::CompositeShape::clone() const
{
  return std::make_unique<CompositeShape>(*this);
}

void rodchenkov::CompositeShape::swap(CompositeShape& r) noexcept
{
  std::swap(rotation_, r.rotation_);
  std::swap(count_   , r.count_   );
  std::swap(capacity_, r.capacity_);
  std::swap(shapes_  , r.shapes_  );
}

void rodchenkov::CompositeShape::rotateShapes(const double drot) noexcept
{
  const point_t centre = getFrameRect().pos;
  for (std::size_t i = 0; i < count_; i++) {
    rectangle_t currFrame = shapes_[i]->getFrameRect();
    const double relativeX = currFrame.pos.x - centre.x;
    const double relativeY = currFrame.pos.y - centre.y;
    const double rotaredX = centre.x + relativeX * cos(drot) - relativeY * sin(drot);
    const double rotatedY = centre.y + relativeX * sin(drot) + relativeY * cos(drot);
    shapes_[i]->move({ rotaredX, rotatedY });
    shapes_[i]->rotate(drot);
  }
}
