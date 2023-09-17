#include <gtest/gtest.h>
#include "lib.h"

TEST(test_gtest_version, test_valid_version) {
    ASSERT_TRUE(version() > 0);
}
