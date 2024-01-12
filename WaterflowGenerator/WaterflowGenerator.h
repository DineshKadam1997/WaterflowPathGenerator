// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the WATERFLOWGENERATOR_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// WATERFLOWGENERATOR_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

// This class is exported from the dll

#include "pch.h"
#include "Point3D.h"
#include<vector>
#include<string>

class WATERFLOWGENERATOR_API WaterflowGenerator {
public:
	WaterflowGenerator(void);
	// TODO: add your methods here.

	std::vector<Point3D> ReadVector(std::string);

public :
	std::vector<float> mVertices;
	std::vector<float> mColors;

	std::string mFileName;
};

extern WATERFLOWGENERATOR_API int nWaterflowGenerator;

WATERFLOWGENERATOR_API int fnWaterflowGenerator(void);
