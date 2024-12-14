// Reader.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "Reader.h"


// This is an example of an exported variable
READER_API int nReader=0;

// This is an example of an exported function.
READER_API int fnReader(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
Reader::Reader()
{
    return;
}

// Function to read stl file
vector<float> Reader::readSTL(string mFileName, std::vector<float>& mNormals)
{
    std::string filePath = mFileName;
    std::ifstream dataFile;
    dataFile.open(filePath);
    if (!dataFile.is_open())
    {
        std::cout << "File not exist" << std::endl;
        return mVertices;
    }

    std::string line;
    while (std::getline(dataFile, line))
    {
        if (line.find("facet normal") != std::string::npos)
        {
            std::string _;
            std::istringstream issNormal(line);
            double x;
            double y;
            double z;
            issNormal >> _ >> _ >> x >> y >> z;
            mNormals.push_back(x);
            mNormals.push_back(y);
            mNormals.push_back(z);
            continue;
        }
        if (line.find("v") != std::string::npos)
        {
            std::istringstream iss(line);
            std::string token;
            double x, y, z;
            iss >> token >> x >> y >> z;
            mVertices.push_back(x * 0.2);
            mVertices.push_back(y * 0.2);
            mVertices.push_back(z * 0.2);


            std::getline(dataFile, line);
            std::istringstream iss1(line);
            std::string token1;
            double x1, y1, z1;
            iss1 >> token1 >> x1 >> y1 >> z1;
            mVertices.push_back(x1 * 0.2);
            mVertices.push_back(y1 * 0.2);
            mVertices.push_back(z1 * 0.2);


            std::getline(dataFile, line);
            std::istringstream iss2(line);
            std::string token2;
            double x2, y2, z2;
            iss2 >> token2 >> x2 >> y2 >> z2;
            mVertices.push_back(x2 * 0.2);
            mVertices.push_back(y2 * 0.2);
            mVertices.push_back(z2 * 0.2);



            //mVertices.push_back(x * 0.2);
            //mVertices.push_back(y * 0.2);
            //mVertices.push_back(z * 0.2);



        }
    }       
    //}
    return mVertices;
}

