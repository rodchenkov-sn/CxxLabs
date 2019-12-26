#include <boost/test/auto_unit_test.hpp>

#define _USE_MATH_DEFINES
#include <cmath>

#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

const double INACCURACY = 1e-6;

BOOST_AUTO_TEST_SUITE(composite_shape_test_suite)

BOOST_AUTO_TEST_CASE(composite_shape_copy_constructor_t)
{
  rodchenkov::CompositeShape testComposite{};
  testComposite.add(rodchenkov::Rectangle{ {5, 5 }, 4, 4 });
  testComposite.add(rodchenkov::Circle{ { 7, 7 }, 2 });
  const std::size_t             originSize  = testComposite.getSize();
  const rodchenkov::rectangle_t originFrame = testComposite.getFrameRect();
  const double                  originArea  = testComposite.getArea();
  rodchenkov::CompositeShape    copyComposite{ testComposite };
  BOOST_CHECK(originSize == copyComposite.getSize());
  BOOST_CHECK_CLOSE(originFrame.width, copyComposite.getFrameRect().width, INACCURACY);
  BOOST_CHECK_CLOSE(originFrame.height, copyComposite.getFrameRect().height, INACCURACY);
  BOOST_CHECK_CLOSE(originFrame.pos.x, copyComposite.getFrameRect().pos.x, INACCURACY);
  BOOST_CHECK_CLOSE(originFrame.pos.y, copyComposite.getFrameRect().pos.y, INACCURACY);
  BOOST_CHECK_CLOSE(originArea, copyComposite.getArea(), INACCURACY);
  copyComposite.scale(2);
  BOOST_CHECK_CLOSE(originFrame.width, testComposite.getFrameRect().width, INACCURACY);
  BOOST_CHECK_CLOSE(originFrame.height, testComposite.getFrameRect().height, INACCURACY);
  BOOST_CHECK_CLOSE(originFrame.pos.x, testComposite.getFrameRect().pos.x, INACCURACY);
  BOOST_CHECK_CLOSE(originFrame.pos.y, testComposite.getFrameRect().pos.y, INACCURACY);
  BOOST_CHECK_CLOSE(originArea, testComposite.getArea(), INACCURACY);
}

BOOST_AUTO_TEST_CASE(composite_shape_adding_t)
{
  rodchenkov::CompositeShape testComposite{};
  const double               width  = 4;
  const double               height = 4;
  const rodchenkov::point_t  pos{ 10, 10 };
  testComposite.add(rodchenkov::Rectangle{ pos, height, width });
  BOOST_CHECK(testComposite.getSize() == 1);
  BOOST_CHECK_CLOSE(testComposite.getFrameRect().width, width, INACCURACY);
  BOOST_CHECK_CLOSE(testComposite.getFrameRect().height, height, INACCURACY);
  BOOST_CHECK_CLOSE(testComposite.getFrameRect().pos.x, pos.x, INACCURACY);
  BOOST_CHECK_CLOSE(testComposite.getFrameRect().pos.y, pos.y, INACCURACY);
  testComposite.add(rodchenkov::Circle{ { 12, 12 }, 2 });
  BOOST_CHECK(testComposite.getSize() == 2);
  BOOST_CHECK_CLOSE(testComposite.getFrameRect().width, 6, INACCURACY);
  BOOST_CHECK_CLOSE(testComposite.getFrameRect().height, 6, INACCURACY);
  BOOST_CHECK_CLOSE(testComposite.getFrameRect().pos.x, 11, INACCURACY);
  BOOST_CHECK_CLOSE(testComposite.getFrameRect().pos.y, 11, INACCURACY);
  testComposite.add(rodchenkov::Rectangle{ {13, 12 }, 10, 12 });
  BOOST_CHECK(testComposite.getSize() == 3);
  BOOST_CHECK_CLOSE(testComposite.getFrameRect().width, 12, INACCURACY);
  BOOST_CHECK_CLOSE(testComposite.getFrameRect().height, 10, INACCURACY);
  BOOST_CHECK_CLOSE(testComposite.getFrameRect().pos.x, 13, INACCURACY);
  BOOST_CHECK_CLOSE(testComposite.getFrameRect().pos.y, 12, INACCURACY);
}

BOOST_AUTO_TEST_CASE(composite_shape_absolute_moving_t)
{
  rodchenkov::CompositeShape testComposite{};
  testComposite.add(rodchenkov::Rectangle{ {0, 0 }, 1, 1 });
  testComposite.add(rodchenkov::Circle{ { 0, 0 }, 1 });
  const double areaBeforeMovement = testComposite.getArea();
  const double widthBeforeMoving  = testComposite.getFrameRect().width;
  const double heightBeforeMoving = testComposite.getFrameRect().height;
  const int    sizeBeforeMoving   = testComposite.getSize();
  testComposite.move({ 1, 1 });
  BOOST_CHECK_CLOSE(testComposite.getArea(), areaBeforeMovement, INACCURACY);
  BOOST_CHECK_CLOSE(testComposite.getFrameRect().width, widthBeforeMoving, INACCURACY);
  BOOST_CHECK_CLOSE(testComposite.getFrameRect().height, heightBeforeMoving, INACCURACY);
  BOOST_CHECK_EQUAL(testComposite.getSize(), sizeBeforeMoving);
}

BOOST_AUTO_TEST_CASE(composite_shape_relative_moving_t)
{
  rodchenkov::CompositeShape testComposite{};
  testComposite.add(rodchenkov::Rectangle{ { 0, 0 }, 1, 1 });
  testComposite.add(rodchenkov::Circle{ { 0, 0 }, 1 });
  const double areaBeforeMovement = testComposite.getArea();
  const double widthBeforeMoving  = testComposite.getFrameRect().width;
  const double heightBeforeMoving = testComposite.getFrameRect().height;
  const int    sizeBeforeMoving   = testComposite.getSize();
  testComposite.move(1, 1);
  BOOST_CHECK_CLOSE(testComposite.getArea(), areaBeforeMovement, INACCURACY);
  BOOST_CHECK_CLOSE(testComposite.getFrameRect().width, widthBeforeMoving, INACCURACY);
  BOOST_CHECK_CLOSE(testComposite.getFrameRect().height, heightBeforeMoving, INACCURACY);
  BOOST_CHECK_EQUAL(testComposite.getSize(), sizeBeforeMoving);
}

BOOST_AUTO_TEST_CASE(composite_shape_upscaling_t)
{
  const double               scalingRatio = 2;
  rodchenkov::CompositeShape testComposite{};
  testComposite.add(rodchenkov::Rectangle{ { 0, 0 }, 1, 1 });
  testComposite.add(rodchenkov::Circle{ { 0, 0 }, 1 });
  const double areaBeforeMovement = testComposite.getArea();
  const double widthBeforeMoving  = testComposite.getFrameRect().width;
  const double heightBeforeMoving = testComposite.getFrameRect().height;
  const int    sizeBeforeMoving   = testComposite.getSize();
  testComposite.scale(scalingRatio);
  BOOST_CHECK_CLOSE(testComposite.getArea(), areaBeforeMovement * pow(scalingRatio, 2), INACCURACY);
  BOOST_CHECK_CLOSE(testComposite.getFrameRect().width, widthBeforeMoving * scalingRatio, INACCURACY);
  BOOST_CHECK_CLOSE(testComposite.getFrameRect().height, heightBeforeMoving * scalingRatio, INACCURACY);
  BOOST_CHECK_EQUAL(testComposite.getSize(), sizeBeforeMoving);
}

BOOST_AUTO_TEST_CASE(composite_shape_downscaling_t)
{
  const double               scalingRatio = 0.5;
  rodchenkov::CompositeShape testComposite{};
  testComposite.add(rodchenkov::Rectangle{ { 0, 0 }, 1, 1 });
  testComposite.add(rodchenkov::Circle{ { 0, 0 }, 1 });
  const double areaBeforeMovement = testComposite.getArea();
  const double widthBeforeMoving  = testComposite.getFrameRect().width;
  const double heightBeforeMoving = testComposite.getFrameRect().height;
  const int    sizeBeforeMoving   = testComposite.getSize();
  testComposite.scale(scalingRatio);
  BOOST_CHECK_CLOSE(testComposite.getArea(), areaBeforeMovement * pow(scalingRatio, 2), INACCURACY);
  BOOST_CHECK_CLOSE(testComposite.getFrameRect().width, widthBeforeMoving * scalingRatio, INACCURACY);
  BOOST_CHECK_CLOSE(testComposite.getFrameRect().height, heightBeforeMoving * scalingRatio, INACCURACY);
  BOOST_CHECK_EQUAL(testComposite.getSize(), sizeBeforeMoving);
}

BOOST_AUTO_TEST_CASE(composite_shape_removing_t)
{
  rodchenkov::CompositeShape testComposite{};
  testComposite.add(rodchenkov::Rectangle{ { 0, 0 }, 10, 10 });
  testComposite.add(rodchenkov::Rectangle{ { 0, 0 }, 20, 20 });
  testComposite.add(rodchenkov::Rectangle{ { 0, 0 }, 30, 30 });
  BOOST_CHECK(testComposite.getSize() == 3);
  rodchenkov::rectangle_t currFrame = testComposite.getFrameRect();
  BOOST_CHECK_CLOSE(currFrame.pos.x, 0, INACCURACY);
  BOOST_CHECK_CLOSE(currFrame.pos.y, 0, INACCURACY);
  BOOST_CHECK_CLOSE(currFrame.width, 30, INACCURACY);
  BOOST_CHECK_CLOSE(currFrame.height, 30, INACCURACY);
  testComposite.remove(2);
  currFrame = testComposite.getFrameRect();
  BOOST_CHECK(testComposite.getSize() == 2);
  BOOST_CHECK_CLOSE(currFrame.pos.x, 0, INACCURACY);
  BOOST_CHECK_CLOSE(currFrame.pos.y, 0, INACCURACY);
  BOOST_CHECK_CLOSE(currFrame.width, 20, INACCURACY);
  BOOST_CHECK_CLOSE(currFrame.height, 20, INACCURACY);
  testComposite.remove(1);
  currFrame = testComposite.getFrameRect();
  BOOST_CHECK(testComposite.getSize() == 1);
  BOOST_CHECK_CLOSE(currFrame.pos.x, 0, INACCURACY);
  BOOST_CHECK_CLOSE(currFrame.pos.y, 0, INACCURACY);
  BOOST_CHECK_CLOSE(currFrame.width, 10, INACCURACY);
  BOOST_CHECK_CLOSE(currFrame.height, 10, INACCURACY);
  testComposite.remove(0);
  currFrame = testComposite.getFrameRect();
  BOOST_CHECK(testComposite.getSize() == 0);
  BOOST_CHECK_CLOSE(currFrame.pos.x, 0, INACCURACY);
  BOOST_CHECK_CLOSE(currFrame.pos.y, 0, INACCURACY);
  BOOST_CHECK_CLOSE(currFrame.width, 0, INACCURACY);
  BOOST_CHECK_CLOSE(currFrame.height, 0, INACCURACY);
}

BOOST_AUTO_TEST_CASE(composite_shape_independent_scaling_t)
{
  rodchenkov::CompositeShape testComposite{};
  testComposite.add(rodchenkov::Rectangle{ { 10, 10 }, 10, 10 });
  testComposite.add(rodchenkov::Circle{ { 15, 15 }, 5 });
  testComposite[1].scale(2);
  rodchenkov::rectangle_t currFrame = testComposite.getFrameRect();
  BOOST_CHECK_CLOSE(currFrame.pos.x, 15, INACCURACY);
  BOOST_CHECK_CLOSE(currFrame.pos.y, 15, INACCURACY);
  BOOST_CHECK_CLOSE(currFrame.width, 20, INACCURACY);
  BOOST_CHECK_CLOSE(currFrame.height, 20, INACCURACY);
  testComposite[0].scale(2);
  currFrame = testComposite.getFrameRect();
  BOOST_CHECK_CLOSE(currFrame.pos.x, 12.5, INACCURACY);
  BOOST_CHECK_CLOSE(currFrame.pos.y, 12.5, INACCURACY);
  BOOST_CHECK_CLOSE(currFrame.width, 25, INACCURACY);
  BOOST_CHECK_CLOSE(currFrame.height, 25, INACCURACY);
}

BOOST_AUTO_TEST_CASE(composite_shape_independent_moving_t)
{
  rodchenkov::CompositeShape testComposite{};
  testComposite.add(rodchenkov::Rectangle{ { 10, 10 }, 10, 10 });
  testComposite.add(rodchenkov::Rectangle{ { 10, 10 }, 10, 10 });
  testComposite.add(rodchenkov::Rectangle{ { 10, 10 }, 10, 10 });
  rodchenkov::rectangle_t currFrame = testComposite.getFrameRect();
  BOOST_CHECK_CLOSE(currFrame.pos.x, 10, INACCURACY);
  BOOST_CHECK_CLOSE(currFrame.pos.y, 10, INACCURACY);
  BOOST_CHECK_CLOSE(currFrame.width, 10, INACCURACY);
  BOOST_CHECK_CLOSE(currFrame.height, 10, INACCURACY);
  testComposite[1].move(10, 0);
  currFrame = testComposite.getFrameRect();
  BOOST_CHECK_CLOSE(currFrame.pos.x, 15, INACCURACY);
  BOOST_CHECK_CLOSE(currFrame.pos.y, 10, INACCURACY);
  BOOST_CHECK_CLOSE(currFrame.width, 20, INACCURACY);
  BOOST_CHECK_CLOSE(currFrame.height, 10, INACCURACY);
  testComposite[2].move(10, 10);
  currFrame = testComposite.getFrameRect();
  BOOST_CHECK_CLOSE(currFrame.pos.x, 15, INACCURACY);
  BOOST_CHECK_CLOSE(currFrame.pos.y, 15, INACCURACY);
  BOOST_CHECK_CLOSE(currFrame.width, 20, INACCURACY);
  BOOST_CHECK_CLOSE(currFrame.height, 20, INACCURACY);
}

BOOST_AUTO_TEST_CASE(composite_shape_rotation_t)
{
  rodchenkov::CompositeShape testComposite{};
  testComposite.add(rodchenkov::Circle{ { 0, 20 }, 5 });
  testComposite.add(rodchenkov::Circle{ { 0, -20 }, 5 });
  const double area = testComposite.getArea();
  const double orbitRadius = 20;
  for (double angle = 0; angle < 2 * M_PI; angle += 0.01) {
    testComposite.setRotation(angle);
    BOOST_CHECK_CLOSE(area, testComposite.getArea(), INACCURACY);
    const double currFirstOrbit = pow(pow(testComposite[0].getFrameRect().pos.x, 2) + pow(testComposite[0].getFrameRect().pos.y, 2), 0.5);
    BOOST_CHECK_CLOSE(orbitRadius, currFirstOrbit, INACCURACY);
    const double currSecondOrbit = pow(pow(testComposite[1].getFrameRect().pos.x, 2) + pow(testComposite[1].getFrameRect().pos.y, 2), 0.5);
    BOOST_CHECK_CLOSE(orbitRadius, currSecondOrbit, INACCURACY);
  }
}

BOOST_AUTO_TEST_CASE(composite_shape_index_operator_exception_t)
{
  rodchenkov::CompositeShape testComposite{};
  BOOST_CHECK_THROW(testComposite[0], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(composite_shape_remove_exception_t)
{
  rodchenkov::CompositeShape testComposite{};
  BOOST_CHECK_THROW(testComposite.remove(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(composite_shape_scaling_exception_t)
{
  rodchenkov::CompositeShape testComposite{};
  testComposite.add(rodchenkov::Rectangle{ { 0, 0 }, 1, 1 });
  BOOST_CHECK_THROW(testComposite.scale(-1), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
