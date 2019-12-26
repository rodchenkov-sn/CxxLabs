#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <ostream>
#include <memory>
#include <cmath>

#include "base-types.hpp"

namespace rodchenkov {

  class Shape
  {
  public:
    virtual ~Shape() = default;

    virtual double                 getArea()                const noexcept = 0;
    virtual double                 getRotation()            const noexcept = 0;
    virtual rectangle_t            getFrameRect()           const noexcept = 0;
    virtual std::unique_ptr<Shape> clone()                  const          = 0;
    virtual void                   printData(std::ostream&) const          = 0;
    virtual void                   move(const point_t&)           noexcept = 0;
    virtual void                   move(double, double)           noexcept = 0;
    virtual void                   setRotation(double)            noexcept = 0;
    virtual void                   rotate(double)                 noexcept = 0;
    virtual void                   scale(double)                           = 0;
  };

  typedef std::unique_ptr<std::unique_ptr<Shape>[]> ShapeArray;
  typedef std::unique_ptr<std::shared_ptr<Shape>[]> SharedShapeArray;

} // namespace rodchenkov

#endif // SHAPE_HPP
