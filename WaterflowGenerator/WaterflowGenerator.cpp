// WaterflowGenerator.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "WaterflowGenerator.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include<algorithm>
#include <string>
#include<vector>


// This is an example of an exported variable
WATERFLOWGENERATOR_API int nWaterflowGenerator=0;

// This is an example of an exported function.
WATERFLOWGENERATOR_API int fnWaterflowGenerator(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
WaterflowGenerator::WaterflowGenerator()
{
    return;
}

std::vector<Point3D> WaterflowGenerator::ReadVector(std::string filePath)
{
    std::string mFileName = filePath;

    std::ifstream dataFile;
    dataFile.open(mFileName);

    std::vector<Point3D> vec;

    if (!dataFile.is_open())
    {
        std::cout << "File not exist" << std::endl;
        return vec;
    }

    std::string line;
    int count = 0;

    std::vector<Point3D> points;

    while (std::getline(dataFile, line))
    {
        if (line.find("vertex") != std::string::npos)
        {
            std::istringstream iss(line);
            std::string token;
            double x, y, z;
            iss >> token >> x >> y >> z;

            Point3D point(x, y, z);
            points.push_back(point);
        }
    }

    // Sort points in descending order of their Y coordinates
    std::sort(points.begin(), points.end(), [](const Point3D& a, const Point3D& b)
        {
            return a.y() > b.y();
        });

    return points;
}