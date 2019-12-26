#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <ostream>
#include <unordered_map>
#include <functional>
#include <memory>

#include "point.hpp"

class Shape
{
public:

  using ShPtr = std::shared_ptr<Shape>;

  explicit Shape(const point_t&);
  virtual ~Shape() = default;

  bool isMoreLeft(const ShPtr&) const;
  bool isUpper   (const ShPtr&) const;

  virtual void draw(std::ostream&) const = 0;

  friend std::ostream& operator << (std::ostream&, const ShPtr&);
  friend std::istream& operator >> (std::istream&, ShPtr&);

protected:

  const point_t centre_;

};

class Circle final : public Shape
{
public:
  explicit Circle(const point_t&);
  void draw(std::ostream&) const override;
};

class Triangle final : public Shape
{
public:
  explicit Triangle(const point_t&);
  void draw(std::ostream&) const override;
};

class Square final : public Shape
{
public:
  explicit Square(const point_t&);
  void draw(std::ostream&) const override;
};

class ShapeFactory
{
public:
  friend std::istream& operator >> (std::istream&, ShapeFactory&);
  Shape::ShPtr produce(const point_t&) const;
private:
  std::string kind_;
  static const std::unordered_map<std::string, std::function<Shape::ShPtr(const point_t&)>> producers;
};

#endif // SHAPES_HPP
