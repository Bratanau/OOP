#include <gtest/gtest.h>
#include "trapezoid.h"
#include "rhombus.h"
#include "pentagon.h"
#include <sstream>

TEST(FigureTest, TrapezoidArea) {
    Trapezoid trap({0, 0}, {4, 0}, {3, 2}, {1, 2});
    EXPECT_NEAR(trap.getArea(), 6.0, 1e-9);
}

TEST(FigureTest, RhombusArea) {
    Rhombus rhomb({0, 0}, {2, 0}, {3, 1}, {1, 1});
    EXPECT_NEAR(rhomb.getArea(), 2.0, 1e-9);
}

TEST(FigureTest, PentagonArea) {
    Pentagon pent({0, 0}, {1, 0}, {1, 1}, {0.5, 1.5}, {0, 1});
    EXPECT_NEAR(pent.getArea(), 1.25, 1e-9);
}

TEST(FigureTest, TrapezoidCenter) {
    Trapezoid trap({0, 0}, {4, 0}, {3, 2}, {1, 2});
    auto center = trap.getCenter();
    EXPECT_DOUBLE_EQ(center.first, 2.0);
    EXPECT_DOUBLE_EQ(center.second, 1.0);
}

TEST(FigureTest, OperatorDouble) {
    Pentagon pent({0, 0}, {1, 0}, {1, 1}, {0.5, 1.5}, {0, 1});
    double area = static_cast<double>(pent);
    EXPECT_NEAR(area, 1.25, 1e-9);
}