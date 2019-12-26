#include <boost/test/auto_unit_test.hpp>
#include "split.hpp"
#include "matrix.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

BOOST_AUTO_TEST_SUITE(split_fun_test_suite)

BOOST_AUTO_TEST_CASE(split_into_layers_t)
{
  rodchenkov::SharedShapeArray testShapes = std::make_unique<std::shared_ptr<rodchenkov::Shape>[]>(8);
  testShapes[0] = std::make_shared<rodchenkov::Rectangle>(rodchenkov::Rectangle{ {0  , 0 }, 10, 10 }); // 1 layer
  testShapes[1] = std::make_shared<rodchenkov::Rectangle>(rodchenkov::Rectangle{ {0  , 20}, 10, 10 }); // 1 layer
  testShapes[2] = std::make_shared<rodchenkov::Rectangle>(rodchenkov::Rectangle{ {20 , 0 }, 10, 10 }); // 1 layer
  testShapes[3] = std::make_shared<rodchenkov::Rectangle>(rodchenkov::Rectangle{ {0  , 0 }, 10, 10 }); // 2 layer
  testShapes[4] = std::make_shared<rodchenkov::Rectangle>(rodchenkov::Rectangle{ {-20, 0 }, 10, 10 }); // 1 layer
  testShapes[5] = std::make_shared<rodchenkov::Rectangle>(rodchenkov::Rectangle{ {20 , 0 }, 10, 10 }); // 2 layer

  testShapes[6] = std::make_shared<rodchenkov::Circle>(rodchenkov::Circle{ {0 , 0 }, 100 }); // 3 layer
  testShapes[7] = std::make_shared<rodchenkov::Circle>(rodchenkov::Circle{ {20, 20}, 10 }); // 1 layer

  rodchenkov::Matrix<std::shared_ptr<rodchenkov::Shape>> splitted = rodchenkov::splitIntoLayers(testShapes, 8);

  //
  //  +---+---+---+---+---+
  //  | 6 | x | x | x | x |
  //  +---+---+---+---+---+
  //  | 3 | 5 | x | x | x |
  //  +---+---+---+---+---+
  //  | 0 | 1 | 2 | 4 | 7 |
  //  +---+---+---+---+---+
  //

  BOOST_CHECK(splitted.rows() == 3);
  BOOST_CHECK(splitted.cols() == 5);
  BOOST_CHECK(!splitted.at(1, 2));
  BOOST_CHECK(!splitted.at(1, 3));
  BOOST_CHECK(!splitted.at(1, 4));
  BOOST_CHECK(!splitted.at(2, 1));
  BOOST_CHECK(!splitted.at(2, 2));
  BOOST_CHECK(!splitted.at(2, 3));
  BOOST_CHECK(!splitted.at(2, 4));
}

BOOST_AUTO_TEST_CASE(split_into_layers_exceptions_t)
{
  rodchenkov::SharedShapeArray testShapes = std::make_unique<std::shared_ptr<rodchenkov::Shape>[]>(8);
  BOOST_CHECK_THROW(rodchenkov::splitIntoLayers(testShapes, 0), std::invalid_argument);
  BOOST_CHECK_THROW(rodchenkov::splitIntoLayers(testShapes, 8), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
