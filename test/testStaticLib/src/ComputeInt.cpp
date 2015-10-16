#include "ComputeInt.h"
#include <stdexcept>

ComputeInt::ComputeInt(int val) : mVal(val) {}

int ComputeInt::add(int val) {
	return mVal + val;
}

int ComputeInt::divide(int d) {
	if (d == 0)
		throw std::runtime_error("Divide by 0 is forbiden");
	return mVal / d;
}