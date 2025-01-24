#include <gtest/gtest.h>

int Add(int a, int b)
{
    return a + b;
}

TEST(AddTest, PositiveNumbers)
{
    int a = 2;
    int b = 3;
    int result = Add(a, b);
    EXPECT_EQ(result, 5);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}