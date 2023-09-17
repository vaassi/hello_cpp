#include <gtest/gtest.h>
#include "lib.h"

TEST(test_gtest_version, test_valid_version) {
    EXPECT_TRUE(version() > 0);
}
