#include <boost/test/unit_test.hpp>
#include "lib.h"

BOOST_AUTO_TEST_SUITE(test_version)

    BOOST_AUTO_TEST_CASE(test_valid_version) {
        BOOST_CHECK(version() > 0);
    }

BOOST_AUTO_TEST_SUITE_END()