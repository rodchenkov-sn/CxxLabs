#include "shapes.hpp"

#include "ioUtils.hpp"

bool Shape::isMoreLeft(const ShPtr& other) const
{
  if (!other) {
    throw std::invalid_argument{ "null was passed as an argument to Shape::isMoreLeft" };
  }
  return centre_.x < other->centre_.x;
}

bool Shape::isUpper(const ShPtr& other) const
{
  if (!other) {
    throw std::invalid_argument{ "null was passed as an argument to Shape::isUpper" };
  }
  return centre_.y > other->centre_.y;
}

Shape::Shape(const point_t& centre):
  centre_(centre)
{
}


std::ostream& operator<<(std::ostream& stream, const Shape::ShPtr& shape)
{
  std::ostream::sentry sentry{ stream };
  if (sentry) {
    shape->draw(stream);
  }
  return stream;
}

std::istream& operator>>(std::istream& stream, Shape::ShPtr& shape)
{
  std::istream::sentry sentry{ stream };
  if (!sentry) {
    return stream;
  }
  FlagGuard flagGuard{ stream };
  point_t point{};
  ShapeFactory factory;
  stream >> std::noskipws;
  stream >> ws >> factory >> ws >> point;
  if (!stream.fail()) {
    const auto sh = factory.produce(point);
    shape = sh;
  }
  return stream;
}

Circle::Circle(const point_t& centre):
  Shape(centre)
{
}

void Circle::draw(std::ostream& stream) const
{
  stream << "CIRCLE " << centre_;
}

Triangle::Triangle(const point_t& centre):
  Shape(centre)
{
}

void Triangle::draw(std::ostream& stream) const
{
  stream << "TRIANGLE " << centre_;
}

Square::Square(const point_t& centre) :
  Shape(centre)
{
}

void Square::draw(std::ostream& stream) const
{
  stream << "SQUARE " << centre_;
}

std::istream& operator>>(std::istream& stream, ShapeFactory& factory)
{
  std::istream::sentry sentry{ stream };
  if (!sentry) {
    return stream;
  }
  const auto kind = readUntil(stream, [](char c) { return isspace(c) || c == '('; });
  if (ShapeFactory::producers.find(kind) == ShapeFactory::producers.end()) {
    stream.setstate(std::ios_base::failbit);
    return stream;
  }
  factory.kind_ = kind;
  return stream;
}

Shape::ShPtr ShapeFactory::produce(const point_t& centre) const
{
  return producers.at(kind_)(centre);
}

const std::unordered_map<std::string, std::function<Shape::ShPtr(const point_t&)>> ShapeFactory::producers = {
  { "CIRCLE"  , [](const point_t& centre) { return std::make_shared<Circle>(centre);   } },
  { "TRIANGLE", [](const point_t& centre) { return std::make_shared<Triangle>(centre); } },
  { "SQUARE"  , [](const point_t& centre) { return std::make_shared<Square>(centre);   } }
};
