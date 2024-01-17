#pragma once
#include "pch.h"
#include "Point3D.h"

// Class representing a triangle in 3D space
class GEOMETRY_API Triangle
{
public:
    Triangle(Point3D p1, Point3D p2, Point3D p3);

    ~Triangle();

    Point3D p1() const;

    Point3D p2() const;

    Point3D p3() const;

private:
    Point3D mP1;
    Point3D mP2;
    Point3D mP3;
};
