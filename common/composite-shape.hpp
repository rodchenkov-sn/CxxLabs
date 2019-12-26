#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace rodchenkov {

  class CompositeShape : public Shape
  {
  public:
    CompositeShape();
    CompositeShape(const CompositeShape&);
    CompositeShape(CompositeShape&&) noexcept;

    const CompositeShape& operator = (const CompositeShape&);
    const CompositeShape& operator = (CompositeShape&&) noexcept;
    Shape& operator [] (std::size_t) const;

    double                 getArea()                const noexcept override;
    double                 getRotation()            const noexcept override;
    rectangle_t            getFrameRect()           const noexcept override;
    std::unique_ptr<Shape> clone()                  const          override;
    void                   printData(std::ostream&) const          override;
    void                   move(const point_t&)           noexcept override;
    void                   move(double, double)           noexcept override;
    void                   setRotation(double)            noexcept override;
    void                   rotate(double)                 noexcept override;
    void                   scale(double)                           override;

    std::size_t getSize() const noexcept;
    void        add(const Shape&);
    void        remove(std::size_t);
    void        resize(std::size_t);

    void swap(CompositeShape&) noexcept;

  private:
    double      rotation_;
    std::size_t count_;
    std::size_t capacity_;
    ShapeArray  shapes_;

    void rotateShapes(double) noexcept;
  };

} // namespace rodchenkov

#endif // COMPOSITE_SHAPE_HPP
