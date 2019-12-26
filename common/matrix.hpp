#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>
#include <stdexcept>

namespace rodchenkov {

  template<typename T>
  class Matrix
  {
  public:
    Matrix(size_t, size_t);
    Matrix(const Matrix<T>&);
    Matrix(Matrix<T>&&) noexcept;

    const Matrix<T>& operator = (const Matrix<T>&);
    const Matrix<T>& operator = (Matrix<T>&&) noexcept;
    bool operator == (const Matrix<T>&) noexcept;
    bool operator != (const Matrix<T>&) noexcept;
    T* operator [] (size_t); // totally unsafe but kinda fast

    size_t rows() const noexcept;
    size_t cols() const noexcept;

    void forEach(void (*fun)(T&));
    void forEachSafe(void (*fun)(T&));
    T& at(size_t, size_t);
    void resize(size_t, size_t);

    void swap(Matrix<T>&) noexcept;

  private:
    size_t               rows_;
    size_t               cols_;
    std::unique_ptr<T[]> items_;
  };

} // namespace rodchenkov

template<typename T>
rodchenkov::Matrix<T>::Matrix(const size_t r, const size_t c) :
  rows_(r),
  cols_(c),
  items_(std::make_unique<T[]>(c* r))
{
}

template<typename T>
rodchenkov::Matrix<T>::Matrix(const Matrix<T>& mx) :
  rows_(mx.rows_),
  cols_(mx.cols_),
  items_(std::make_unique<T[]>(cols_* rows_))
{
  for (size_t i = 0; i < cols_ * rows_; i++) {
    items_[i] = mx.items_[i];
  }
}

template<typename T>
rodchenkov::Matrix<T>::Matrix(Matrix<T>&& mx) noexcept
{
  swap(mx);
}

template<typename T>
const rodchenkov::Matrix<T>& rodchenkov::Matrix<T>::operator=(const Matrix<T>& mx)
{
  Matrix<T> temp(mx);
  swap(temp);
  return *this;
}

template<typename T>
const rodchenkov::Matrix<T>& rodchenkov::Matrix<T>::operator=(Matrix<T>&& mx) noexcept
{
  swap(mx);
  return *this;
}

template<typename T>
bool rodchenkov::Matrix<T>::operator==(const Matrix<T>& rhs) noexcept
{
  if ((rows_ != rhs.rows_) || (cols_ != rhs.cols_)) {
    return false;
  }

  try {

    for (size_t i = 0; i < cols_ * rows_; i++) {
      if (items_[i] != rhs.items_[i]) {
        return false;
      }
    }

  } catch (...) {
    return false;
  }

  return true;
}

template<typename T>
bool rodchenkov::Matrix<T>::operator!=(const Matrix<T>& rhs) noexcept
{
  return !(*this == rhs);
}

template<typename T>
T* rodchenkov::Matrix<T>::operator[](const size_t n)
{
  return &items_[n * cols_];
}

template<typename T>
size_t rodchenkov::Matrix<T>::rows() const noexcept
{
  return rows_;
}

template<typename T>
size_t rodchenkov::Matrix<T>::cols() const noexcept
{
  return cols_;
}

template<typename T>
void rodchenkov::Matrix<T>::forEach(void(*fun)(T&))
{
  for (size_t i = 0; i < cols_ * rows_; i++) {
    fun(items_[i]);
  }
}

template<typename T>
inline void rodchenkov::Matrix<T>::forEachSafe(void(*fun)(T&))
{
  for (size_t i = 0; i < cols_ * rows_; i++) {
    if (items_[i]) {
      fun(items_[i]);
    }
  }
}

template<typename T>
T& rodchenkov::Matrix<T>::at(const size_t r, const size_t c)
{
  if (r >= rows_ || c >= cols_) {
    throw std::out_of_range("indexes were out of range in Matrix::at");
  }
  return items_[r * cols_ + c];
}

template<typename T>
void rodchenkov::Matrix<T>::resize(const size_t r, const size_t c)
{
  if ((r > rows_ && c >= cols_) || (r >= rows_ && c > cols_)) {
    std::unique_ptr<T[]> newItems = std::make_unique<T[]>(c * r);
    for (size_t i = 0; i < rows_; i++) {
      for (size_t j = 0; j < cols_; j++) {
        newItems[i * c + j] = at(i, j);
      }
    }
    std::swap(items_, newItems);
    rows_ = r;
    cols_ = c;
  }
}

template<typename T>
void rodchenkov::Matrix<T>::swap(Matrix<T>& mx) noexcept
{
  std::swap(cols_, mx.cols_);
  std::swap(rows_, mx.rows_);
  std::swap(items_, mx.items_);
}

#endif // MATRIX_HPP
