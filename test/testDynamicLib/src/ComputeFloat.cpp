#include "ComputeFloat.h"
#include <stdexcept>

ComputeFloat::ComputeFloat(float val) : mVal(val) {}

float ComputeFloat::add(float val) {
	return mVal + val;
}

float ComputeFloat::divide(float d) {
	if (d == 0)
		throw std::runtime_error("Divide by 0 is forbiden");
	return mVal / d;
}
