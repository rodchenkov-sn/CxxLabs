#ifndef SPLIT_HPP
#define SPLIT_HPP

#include "shape.hpp"
#include "matrix.hpp"

namespace rodchenkov {

  Matrix<std::shared_ptr<Shape>> splitIntoLayers(const SharedShapeArray&, size_t);

} // namespace rodchenkov

#endif // SPLIT_HPP
