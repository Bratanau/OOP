#include <gtest/gtest.h>
#include "seven.h"
#include <sstream>

std::string SevenToString(const Seven& num) {
    std::ostringstream oss;
    num.print(oss);
    return oss.str();
}

TEST(SevenTest, BasicStringConstructor) {
    Seven a("11");
    EXPECT_EQ(SevenToString(a), "11");
}

TEST(SevenTest, Addition) {
    Seven a("11");
    Seven b("16");
    Seven result = a.add(b);
    EXPECT_EQ(SevenToString(result), "30");
}

TEST(SevenTest, Comparison) {
    Seven a("1");
    Seven b("11");
    EXPECT_TRUE(a.less(b));
    EXPECT_TRUE(b.greater(a));
    EXPECT_FALSE(a.equals(b));
}

TEST(SevenTest, EqualNumbers) {
    Seven a("11");
    Seven b("11");
    EXPECT_TRUE(a.equals(b));
    EXPECT_FALSE(a.less(b));
}

TEST(SevenTest, InvalidStringThrows) {
    EXPECT_THROW(Seven("1Z3"), std::invalid_argument);
    EXPECT_THROW(Seven(""), std::invalid_argument);
}

TEST(SevenTest, CopyConstructor) {
    Seven a("45");
    Seven b = a;
    EXPECT_TRUE(b.equals(a));
}

TEST(SevenTest, CopyMethod) {
    Seven a("45");
    Seven b = a.copy();
    EXPECT_TRUE(b.equals(a));
}

TEST(SevenTest, MoveConstructor) {
    Seven a("45");
    Seven c(std::move(a));
    EXPECT_EQ(SevenToString(c), "45");
}

TEST(SevenTest, PrintMethod) {
    Seven a("66");
    std::ostringstream oss;
    a.print(oss);
    EXPECT_EQ(oss.str(), "66");
}

TEST(SevenTest, SubtractionThrowsWhenNegative) {
    Seven a("15");
    Seven b("20");
    EXPECT_THROW(a.subtract(b), std::logic_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}