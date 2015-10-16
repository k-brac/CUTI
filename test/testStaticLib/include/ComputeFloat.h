#ifndef CUTI_COMPUTE_FLOAT
#define CUTI_COMPUTE_FLOAT

class ComputeFloat
{
private:
	float mVal = 0.f;
public:
	ComputeFloat(float val);
	float add(float val);
	float divide(float d);
};
#endif