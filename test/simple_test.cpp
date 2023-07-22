#include <gtest/gtest.h>

TEST(SimpleTest, ItWorks)
{
    constexpr int answer = 42;
    EXPECT_EQ(answer, 42);
}
