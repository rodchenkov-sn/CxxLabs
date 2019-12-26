#include "split.hpp"
#include <stdexcept>

rodchenkov::Matrix<std::shared_ptr<rodchenkov::Shape>> rodchenkov::splitIntoLayers(const SharedShapeArray& shapes, const size_t size)
{
  if (size == 0) {
    throw std::invalid_argument("size can\'t be zero");
  }
  Matrix<std::shared_ptr<Shape>> matrix(1, 1);
  matrix[0][0] = shapes[0];
  if (!shapes[0]) {
    throw std::invalid_argument("all shapes mustn\'t be null");
  }
  size_t maxRow = 1;
  size_t maxCol = 1;

  for (size_t i = 1; i < size; i++) {

    if (!shapes[i]) {
      throw std::invalid_argument("all shapes mustn\'t be null");
    }

    const rectangle_t currFrame = shapes[i]->getFrameRect();

    for (size_t row = 0; row < maxRow; row++) {

      bool hasIntersected = false;
      bool wasInserted    = false;

      for (size_t col = 0; col < maxCol; col++) {

        if (matrix[row][col] && isIntersected(currFrame, matrix.at(row, col)->getFrameRect())) {
          hasIntersected = true;
          break;
        }
        if (!matrix[row][col] && !hasIntersected) {
          matrix[row][col] = shapes[i];
          wasInserted = true;
          break;
        }

      }

      if (hasIntersected && row == maxRow - 1) {
        matrix.resize(maxRow + 1, maxCol);
        matrix[maxRow][0] = shapes[i];
        ++maxRow;
        break;
      }
      if (wasInserted) {
        break;
      }
      if (!hasIntersected && !wasInserted) {
        matrix.resize(maxRow, maxCol + 1);
        matrix[row][maxCol] = shapes[i];
        ++maxCol;
        break;
      }

    }

  }

  return matrix;
}
