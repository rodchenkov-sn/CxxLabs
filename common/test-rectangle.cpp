#include <boost/test/auto_unit_test.hpp>

#define _USE_MATH_DEFINES
#include <cmath>
#include "rectangle.hpp"

const double INACCURACY = 1e-6;

BOOST_AUTO_TEST_SUITE(rectangle_test_suite)

BOOST_AUTO_TEST_CASE(rectangle_absolute_moving_t)
{
  rodchenkov::Rectangle testRectangle{ { 0, 0 }, 1, 1 };
  const double          widthBeforeMoving  = testRectangle.getWidth();
  const double          heightBeforeMoving = testRectangle.getHeight();
  const double          areaBeforeMoving   = testRectangle.getArea();
  testRectangle.move({ 1, 1 });
  BOOST_CHECK_CLOSE(widthBeforeMoving, testRectangle.getWidth(), INACCURACY);
  BOOST_CHECK_CLOSE(heightBeforeMoving, testRectangle.getHeight(), INACCURACY);
  BOOST_CHECK_CLOSE(areaBeforeMoving, testRectangle.getArea(), INACCURACY);
}

BOOST_AUTO_TEST_CASE(rectangle_relative_moving_t)
{
  rodchenkov::Rectangle testRectangle{ { 0, 0 }, 1, 1 };
  const double          widthBeforeMoving  = testRectangle.getWidth();
  const double          heightBeforeMoving = testRectangle.getHeight();
  const double          areaBeforeMoving   = testRectangle.getArea();
  testRectangle.move(1, 1);
  BOOST_CHECK_CLOSE(widthBeforeMoving, testRectangle.getWidth(), INACCURACY);
  BOOST_CHECK_CLOSE(heightBeforeMoving, testRectangle.getHeight(), INACCURACY);
  BOOST_CHECK_CLOSE(areaBeforeMoving, testRectangle.getArea(), INACCURACY);
}

BOOST_AUTO_TEST_CASE(rectangle_upscaling_t)
{
  const double          scalingRatio = 2;
  rodchenkov::Rectangle testRectangle{ { 0, 0 }, 1, 1 };
  const double          areaBeforeScaling   = testRectangle.getArea();
  const double          heightBeforeScaling = testRectangle.getHeight();
  const double          widthBeforeScaling  = testRectangle.getWidth();
  testRectangle.scale(scalingRatio);
  BOOST_CHECK_CLOSE(testRectangle.getArea(), areaBeforeScaling * pow(scalingRatio, 2), INACCURACY);
  BOOST_CHECK_CLOSE(testRectangle.getHeight(), heightBeforeScaling * scalingRatio, INACCURACY);
  BOOST_CHECK_CLOSE(testRectangle.getWidth(), widthBeforeScaling * scalingRatio, INACCURACY);
}

BOOST_AUTO_TEST_CASE(rectangle_downscaling_t)
{
  const double          scalingRatio = 0.5;
  rodchenkov::Rectangle testRectangle{ { 0, 0 }, 1, 1 };
  const double          areaBeforeScaling = testRectangle.getArea();
  testRectangle.scale(scalingRatio);
  BOOST_CHECK_CLOSE(testRectangle.getArea(), areaBeforeScaling * pow(scalingRatio, 2), INACCURACY);
}

BOOST_AUTO_TEST_CASE(rectangle_rotation_t)
{
  rodchenkov::Rectangle testLine{ { 0, 0 }, 10, 0 };
  const double length = testLine.getHeight();
  for (double angle = 0; angle < 2 * M_PI; angle += 0.01) {
    testLine.setRotation(angle);
    const double frameHeight = testLine.getFrameRect().height;
    const double frameWidth = testLine.getFrameRect().width;
    BOOST_CHECK_CLOSE(fabs(length * cos(angle)), frameHeight, INACCURACY);
    BOOST_CHECK_SMALL(fabs(length * sin(angle)) - frameWidth, INACCURACY);
  }
  rodchenkov::Rectangle testRectangle{ { 0, 0 }, 10, 10 };
  const double width = 10;
  const double height = 10;
  const double area = testRectangle.getArea();
  const double diagonal = 10 * pow(2, 0.5);
  for (double angle = 0; angle < M_PI / 2; angle += 0.01) {
    testRectangle.setRotation(angle);
    const double frameWidth = testRectangle.getFrameRect().width;
    BOOST_CHECK_CLOSE(fabs(diagonal * sin(angle + M_PI / 4)), frameWidth, INACCURACY);
    BOOST_CHECK_CLOSE(width, testRectangle.getWidth(), INACCURACY);
    BOOST_CHECK_CLOSE(height, testRectangle.getHeight(), INACCURACY);
    BOOST_CHECK_CLOSE(area, testRectangle.getArea(), INACCURACY);
  }
}

BOOST_AUTO_TEST_CASE(rectangle_constructor_exception_t)
{
  BOOST_CHECK_THROW(rodchenkov::Rectangle testRectangle({ 0, 0 }, -1, 1), std::invalid_argument);
  BOOST_CHECK_THROW(rodchenkov::Rectangle testRectangle({ 0, 0 }, 1, -1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(rectangle_scalig_exception_t)
{
  rodchenkov::Rectangle testRectangle{ { 0, 0 }, 1, 1 };
  BOOST_CHECK_THROW(testRectangle.scale(-1), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
