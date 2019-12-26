#include <boost/test/auto_unit_test.hpp>
#include <stdexcept>
#include "matrix.hpp"

BOOST_AUTO_TEST_SUITE(matrix_test_suite)

BOOST_AUTO_TEST_CASE(matrix_constructors_t)
{
  rodchenkov::Matrix<unsigned int> testMatrix(3, 2);
  BOOST_CHECK(testMatrix.rows() == 3);
  BOOST_CHECK(testMatrix.cols() == 2);
  for (size_t i = 0; i < testMatrix.rows(); i++) {
    for (size_t j = 0; j < testMatrix.cols(); j++) {
      testMatrix.at(i, j) = i * 3 + j + 1;
    }
  }
  rodchenkov::Matrix<unsigned int> copyMatrix(testMatrix);
  BOOST_CHECK(copyMatrix.rows() == 3);
  BOOST_CHECK(copyMatrix.cols() == 2);
  for (size_t i = 0; i < copyMatrix.rows(); i++) {
    for (size_t j = 0; j < copyMatrix.cols(); j++) {
      BOOST_CHECK(copyMatrix.at(i, j) == i * 3 + j + 1);
    }
  }
  rodchenkov::Matrix<unsigned int> moveMatrix(std::move(copyMatrix));
  BOOST_CHECK(moveMatrix.rows() == 3);
  BOOST_CHECK(moveMatrix.cols() == 2);
  for (size_t i = 0; i < moveMatrix.rows(); i++) {
    for (size_t j = 0; j < moveMatrix.cols(); j++) {
      BOOST_CHECK(moveMatrix.at(i, j) == i * 3 + j + 1);
    }
  }
}

BOOST_AUTO_TEST_CASE(matrix_resizing_t)
{
  rodchenkov::Matrix<unsigned int> testMatrix(3, 2);
  for (size_t i = 0; i < testMatrix.rows(); i++) {
    for (size_t j = 0; j < testMatrix.cols(); j++) {
      testMatrix.at(i, j) = i * 3 + j + 1;
    }
  }
  testMatrix.resize(1, 1);
  BOOST_CHECK(testMatrix.rows() == 3);
  BOOST_CHECK(testMatrix.cols() == 2);
  testMatrix.resize(5, 5);
  BOOST_CHECK(testMatrix.rows() == 5);
  BOOST_CHECK(testMatrix.cols() == 5);
  for (size_t i = 0; i < 3; i++) {
    for (size_t j = 0; j < 2; j++) {
      BOOST_CHECK(testMatrix.at(i, j) == i * 3 + j + 1);
    }
  }
}

BOOST_AUTO_TEST_CASE(matrix_comparation_t)
{
  rodchenkov::Matrix<int> fstMatrix(1, 1), sndMatrix(1, 1);
  fstMatrix[0][0] = 1;
  sndMatrix[0][0] = 1;
  BOOST_CHECK(fstMatrix == sndMatrix);
  sndMatrix[0][0] = -1;
  BOOST_CHECK(fstMatrix != sndMatrix);
  fstMatrix[0][0] = -1;
  fstMatrix.resize(2, 1);
  BOOST_CHECK(fstMatrix != sndMatrix);
}

BOOST_AUTO_TEST_CASE(matrix_for_each_t)
{
  rodchenkov::Matrix<int> testMatrix(2, 2), finalMatrix(2, 2);
  finalMatrix[0][0] = 1;
  finalMatrix[0][1] = 1;
  finalMatrix[1][0] = 1;
  finalMatrix[1][1] = 1;
  testMatrix.forEach([](int& i) { i++; });
  BOOST_CHECK(testMatrix == finalMatrix);
  finalMatrix[1][1] = 0;
  testMatrix.forEach([](int& i) { i++; });
  testMatrix[1][1] = 0;
  testMatrix.forEachSafe([](int& i) { i--; });
  BOOST_CHECK(testMatrix == finalMatrix);
}

BOOST_AUTO_TEST_CASE(matrix_exception_t)
{
  rodchenkov::Matrix<int> testMatrix(3, 2);
  BOOST_CHECK_THROW(testMatrix.at(3, 3), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()
