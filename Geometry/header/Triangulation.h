#pragma once
#include "pch.h"
#include "Triangle.h"
#include <vector>

// Class representing a collection of triangles forming a triangulation
class GEOMETRY_API Triangulation
{
public:
    Triangulation(const std::vector<Triangle>& inTriangles);

    ~Triangulation();

    std::vector<Triangle> getTriangles() const;

private:
    std::vector<Triangle> mTriangles;
};
