#pragma once

#include "Core\Core.h"
#include "Math.h"

namespace SnowGaze
{
	namespace Math
	{
		template<typename T>
		inline T Abs(T value)
		{
			return value > 0 ? value : -value;
		}

		template<typename T>
		T Radians(T value)
		{
			return static_cast<T>(PI) * value / 180.0f;
		}

		template<typename T, typename U, typename V>
		T Clamp(T val, U low, V high) {
			if (val < low)
				return low;
			else if (val > high)
				return high;
			else
				return val;
		}

		inline float GetLerp(float t, float v1, float v2)
		{
			return (1.0f - t) * v1 + t * v2;
		}
	}
}
