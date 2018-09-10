#pragma once

#include "Core\Core.h"
#include "Math.h"

#include <algorithm>

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
		Vector3<T> Abs(const Vector3<T>& v)
		{
			return Vector3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z));
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

		inline bool Quadratic(float a, float b, float c, float* t0, float* t1)
		{
			double discrim = (double)b * (double)b - 4 * (double)a * (double)c;

			// no real roots
			if (discrim < 0) 
				return false;

			double rootDiscrim = std::sqrt(discrim);
			double q;
			if (b < 0) 
				q = -.5 * (b - rootDiscrim);
			else 
				q = -.5 * (b + rootDiscrim);
			*t0 = (float)(q / a);
			*t1 = (float)(c / q);
			if (*t0 > *t1) 
				std::swap(*t0, *t1);
			return true;
		}
	}
}
