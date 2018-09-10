#pragma once

namespace SnowGaze
{
	template<typename T> class Vector3;

	namespace Math
	{
		template<typename T>
		T Abs(T value);

		template<typename T>
		Vector3<T> Abs(const Vector3<T>& v);

		float GetLerp(float t, float v1, float v2);

		template<typename T>
		T Radians(T value);

		template <typename T, typename U, typename V>
		inline T Clamp(T val, U low, V high);

		bool Quadratic(float a, float b, float c, float *t0, float *t1);
	}
}

#include "Core/Geometry/Math.hpp"
