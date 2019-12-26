#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace rodchenkov {

  class Rectangle : public Shape
  {
  public:
    Rectangle(const point_t&, double, double);
    Rectangle(const point_t&, double, double, double);

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

    double getWidth() const noexcept;
    double getHeight() const noexcept;

  private:
    double      height_;
    double      width_;
    double      rotation_;
    rectangle_t frame_rect_;

    void computeFrame() noexcept;

  };

} // namespace rodchenkov

#endif // RECTANGLE_HPP
