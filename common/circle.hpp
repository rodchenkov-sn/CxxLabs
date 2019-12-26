#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace rodchenkov {

  class Circle : public Shape
  {
  public:
    Circle(const point_t&, double);

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

    double getRadius() const noexcept;

  private:
    double      radius_;
    rectangle_t frame_rect_;
  };

} // namespace rodchenkov

#endif // CIRCLE_HPP
