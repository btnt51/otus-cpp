

#include "lib.h"
#include "googletest/googletest/include/gtest/gtest.h"

TEST(test_build, buildVER)
{
    EXPECT_GE(build(), 0);
}
