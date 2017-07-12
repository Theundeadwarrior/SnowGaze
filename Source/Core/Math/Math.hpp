#pragma once

#include <math.h>

namespace Core
{
	namespace Math
	{
		template<typename T>
		inline T Abs(T value)
		{
			return value > 0 ? value : -value;
		}

		float GetLerp(float t, float v1, float v2)
		{
			return (1.0f - t) * v1 + t * v2;
		}
	}
}
