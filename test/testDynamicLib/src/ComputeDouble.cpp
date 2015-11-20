#include "ComputeDouble.h"
#include <stdexcept>

ComputeDouble::ComputeDouble(double val) : mVal(val) {}

double ComputeDouble::add(double val) {
	return mVal + val;
}

double ComputeDouble::divide(double d) {
	if (d == 0)
		throw std::runtime_error("Divide by 0 is forbiden");
	return mVal / d;
}
