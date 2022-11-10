#pragma once
#include <cmath>


namespace ISQRT
{
	float Func1(float x)
	{
		return 1.0f / sqrtf(x);
	}

	float Func2(float x)
	{
		return powf(x, -1.0f / 2.0f);
	}

	float Func3(float x)
	{
		long i;
		float x2, y;
		const float threehalfs = 1.5F;

		x2 = x * 0.5F;
		y = x;
		i = *(long*)&y;                       // evil floating point bit level hacking
		i = 0x5f3759df - (i >> 1);            // what the fuck? 
		y = *(float*)&i;
		y = y * (threehalfs - (x2 * y * y));  // iteration

		return y;
	}
}
