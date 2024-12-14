#include "pch.h"

TEST(TestCaseName, TestName) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}


#include "gtest/gtest.h"
#include "Point3D.h"

TEST(Point3DTest, DefaultConstructor) {
    Point3D point(0.0,0.0);
    EXPECT_FLOAT_EQ(point.x(), 0.0f);
    EXPECT_FLOAT_EQ(point.y(), 0.0f);
}

TEST(Point3DTest, ParameterizedConstructor) {
    Point3D point(1.0f, 2.0f);
    EXPECT_FLOAT_EQ(point.x(), 1.0f);
    EXPECT_FLOAT_EQ(point.y(), 2.0f);
}

TEST(Point3DTest, SettersAndGetters) {
    Point3D point(3.0,4.0);
   /* point.setX(3.0f);
    point.setY(4.0f);*/

    EXPECT_FLOAT_EQ(point.x(), 4.0f);
    EXPECT_FLOAT_EQ(point.y(), 4.0f);
}

// Add more tests as needed for other functionality of the Point3D class.

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}