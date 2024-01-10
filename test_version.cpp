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

// Demonstrate some basic assertions.
TEST(test_version, BasicAssertions) {
  // Expect no equality.
  EXPECT_NE(version(), 100);
}
