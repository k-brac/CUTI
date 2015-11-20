#ifndef CUTI_COMPUTE_FLOAT
#define CUTI_COMPUTE_FLOAT

#include "DynamicLib.h"

class LIBRARY_API ComputeFloat
{
private:
	float mVal = 0.f;
public:
	ComputeFloat(float val);
	float add(float val);
	float divide(float d);
};
#endif