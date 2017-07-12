#pragma once

namespace Core
{
	namespace Math
	{
		template<typename T>
		T Abs(T value);

		float GetLerp(float t, float v1, float v2);
	}
}

#include "Core/Math/Math.hpp"
