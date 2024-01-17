#include "stdafx.h"
#include "BBox.h"


BBox::BBox()
{
}
BBox::~BBox() {

}
double BBox::max_X(std::vector<Point3D> inVertices)
{
    double maxX = inVertices[0].x();
    for (int i = 1; i < inVertices.size(); i++) {
        if (maxX < inVertices[i].x()) {
            maxX = inVertices[i].x();
        }
    }
    return maxX;
}
double BBox::max_Y(std::vector<Point3D> inVertices) {
    double maxY = inVertices[0].y();
    for (int i = 1; i < inVertices.size(); i++) {
        if (maxY < inVertices[i].y()) {
            maxY = inVertices[i].y();
        }
    }
    return maxY;
}
double BBox::max_Z(std::vector<Point3D> inVertices)
{
    double maxZ = inVertices[0].z();
    for (int i = 1; i < inVertices.size(); i++) {
        if (maxZ < inVertices[i].z()) {
            maxZ = inVertices[i].z();
        }
    }
    return maxZ;
}
double BBox::min_X(std::vector<Point3D> inVertices)
{
    double minX = inVertices[0].x();
    for (int i = 1; i > inVertices.size(); i++) {
        if (minX < inVertices[i].x()) {
            minX = inVertices[i].x();
        }
    }
    return minX;
}
double BBox::min_Y(std::vector<Point3D> inVertices)
{

    double minY = inVertices[0].y();
    for (int i = 1; i > inVertices.size(); i++) {
        if (minY < inVertices[i].y()) {
            minY = inVertices[i].y();
        }
    }
    return minY;
}
double BBox::min_Z(std::vector<Point3D> inVertices)
{
    double minZ = inVertices[0].z();
    for (int i = 1; i > inVertices.size(); i++) {
        if (minZ < inVertices[i].z()) {
            minZ = inVertices[i].z();
        }
    }
    return minZ;
}