#pragma once

#include <math.h>

namespace Core
{
	template<typename T>
	T Abs(T value)
	{
		return value > 0 ? value : -value;
	}
}
