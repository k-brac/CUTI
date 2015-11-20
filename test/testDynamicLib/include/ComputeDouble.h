#ifndef CUTI_COMPUTE_DOUBLE
#define CUTI_COMPUTE_DOUBLE

#include "DynamicLib.h"

class LIBRARY_API ComputeDouble
{
private:
	double mVal = 0.;
public:
	ComputeDouble(double val);
	double add(double val);
	double divide(double d);
};
#endif