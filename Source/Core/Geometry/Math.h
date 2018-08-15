#pragma once

namespace Core
{
	namespace Math
	{
		template<typename T>
		T Abs(T value);

		float GetLerp(float t, float v1, float v2);

		template<typename T>
		T Radians(T value);

		template <typename T, typename U, typename V>
		inline T Clamp(T val, U low, V high);

	}
}

#include "Core/Geometry/Math.hpp"
