#pragma once
#include "Point3D.h"
#include<vector>
using namespace std;

class BBox
{
public:
	BBox();
	~BBox();
public:
	double max_X(std::vector<Point3D> inVertices);
	double max_Y(std::vector<Point3D> inVertices);
	double max_Z(std::vector<Point3D> inVertices);
	double min_X(std::vector<Point3D> inVertices);
	double min_Y(std::vector<Point3D> inVertices);
	double min_Z(std::vector<Point3D> inVertices);
};

