#define BOOST_TEST_MODULE test_build

#include "lib.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_build)

BOOST_AUTO_TEST_CASE(test_valid_build) {
	BOOST_CHECK(build() > 0);
}

BOOST_AUTO_TEST_SUITE_END()
