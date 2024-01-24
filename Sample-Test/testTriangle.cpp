#include "pch.h"
#include "Triangle.h"

GeometricEntity::Point3D p1(1.0f, 2.0f, 3.0f);
GeometricEntity::Point3D p2(4.0f, 5.0f, 6.0f);
GeometricEntity::Point3D p3(7.0f, 8.0f, 9.0f);

GeometricEntity::Triangle triangle(p1, p2, p3);


TEST(TriangleTest, ConstructorAndGetters) {


    EXPECT_EQ(triangle.p1(), p1);
    EXPECT_EQ(triangle.p2(), p2);
    EXPECT_EQ(triangle.p3(), p3);
    EXPECT_EQ(triangle.normal(), GeometricEntity::Point3D(0, 0, 0)); // Assuming default normal is (0, 0, 0)
}

TEST(TriangleTest, SetNormal) {
    GeometricEntity::Point3D normal(1.0f, 2.0f, 3.0f);
    triangle.setNormal(normal);
    EXPECT_EQ(triangle.normal(), normal);
}

// Test case for Triangle class operator==
TEST(TriangleTest, EqualityOperator) 
{
    GeometricEntity::Point3D p1(1, 2, 3);
    GeometricEntity::Point3D p2(4, 5, 6);
    GeometricEntity::Point3D p3(7, 8, 9);
    GeometricEntity::Triangle triangle1(p1, p2, p3);
    GeometricEntity::Triangle triangle2(p1, p2, p3);

    // Act & Assert
    EXPECT_EQ(triangle1, triangle2);
}