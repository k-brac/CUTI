#ifndef CUTI_COMPUTE_INT
#define CUTI_COMPUTE_INT

#include "DynamicLib.h"

class LIBRARY_API ComputeInt
{
private:
	int mVal = 0;
public:
	ComputeInt(int val);
	int add(int val);
	int divide(int d);
};
#endif
