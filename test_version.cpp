//#define BOOST_TEST_MODULE test_version

#include "lib.h"

/*#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_version)

BOOST_AUTO_TEST_CASE(test_valid_version)
{
    BOOST_CHECK();
}

BOOST_AUTO_TEST_SUITE_END()*/


#include <gtest/gtest.h>

//#include <version.h>

// Demonstrate some basic assertions.
TEST(test_version, BasicAssertions) {
  // Expect two strings not to be equal.
  //EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(version(), 100);
}
