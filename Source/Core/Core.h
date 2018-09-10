#pragma once

#include <limits>
#include <stdint.h>

#define USING(x) (4 / (x) - x)
#define NOT_USING(x) (4 / (x) - 4)

#define IN_USE 1
#define NOT_IN_USE 2

#define F32_NEAR_ZERO 0.00000001f

namespace SnowGaze
{
	static const float MachineEpsilon(std::numeric_limits<float>::epsilon() * 0.5f);
	static const float PI = 3.14159265358979323846f;
	static const float INV_PI = 0.31830988618379067154f;
	static const float INV_2PI = 0.15915494309189533577f;
	static const float INV_4PI = 0.07957747154594766788f;
	static const float PI_OVER2 = 1.57079632679489661923f;
	static const float PI_OVER4 = 0.78539816339744830961f;
	static const float SQRT_2 = 1.41421356237309504880f;

	inline float Radians(float deg) { return (PI / 180) * deg; }
	inline float Degrees(float rad) { return (180 * INV_PI) * rad; }
	inline float Gamma(uint32_t n) { return (n * MachineEpsilon) / (1 - n * MachineEpsilon); }

	inline uint32_t FloatToBits(float f) {
		uint32_t ui;
		memcpy(&ui, &f, sizeof(float));
		return ui;
	}

	inline float BitsToFloat(uint32_t ui) {
		float f;
		memcpy(&f, &ui, sizeof(uint32_t));
		return f;
	}

	inline float NextFloatDown(float v) {
		// Handle infinity and positive zero for _NextFloatDown()_
		if (std::isinf(v) && v < 0.) return v;
		if (v == 0.f) v = -0.f;
		uint32_t ui = FloatToBits(v);
		if (v > 0)
			--ui;
		else
			++ui;
		return BitsToFloat(ui);
	}

	inline float NextFloatUp(float v) {
		// Handle infinity and negative zero for _NextFloatUp()_
		if (std::isinf(v) && v > 0.) return v;
		if (v == -0.f) v = 0.f;

		// Advance _v_ to next higher float
		uint32_t ui = FloatToBits(v);
		if (v >= 0)
			++ui;
		else
			--ui;
		return BitsToFloat(ui);
	}
}

#define INTEL_INTRINSICS NOT_IN_USE
//
//<mmintrin.h>  MMX
//
//<xmmintrin.h> SSE
//
//<emmintrin.h> SSE2
//
//<pmmintrin.h> SSE3
//
//<tmmintrin.h> SSSE3
//
//<smmintrin.h> SSE4.1
//
//<nmmintrin.h> SSE4.2
//
//<ammintrin.h> SSE4A
//
//<wmmintrin.h> AES
//
//<immintrin.h> AVX
//
//<zmmintrin.h> AVX512
