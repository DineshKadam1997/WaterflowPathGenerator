#include "pch.h"
#include "Triangle.h"

// Constructor for the Triangle class
Triangle::Triangle(Point3D inP1, Point3D inP2, Point3D inP3)
    : mP1(0, 0, 0),
    mP2(0, 0, 0),
    mP3(0, 0, 0)
{
    // Assign the input points to the member variables
    mP1 = inP1;
    mP2 = inP2;
    mP3 = inP3;
}


Triangle::~Triangle()
{
}


Point3D Triangle::p1() const
{
    return mP1;
}


Point3D Triangle::p2() const
{
    return mP2;
}


Point3D Triangle::p3() const
{
    return mP3;
}
