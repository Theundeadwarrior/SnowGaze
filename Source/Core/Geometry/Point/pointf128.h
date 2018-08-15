#pragma once

#include <nmmintrin.h>
#include <inttypes.h>

namespace Core
{
	class Vector4f128;

	class Point4f128
	{
	public:
		Point4f128() = default;
		Point4f128(float x, float y, float z, float w = 0.0f);
		~Point4f128() = default;
		
		Point4f128 operator+(const Vector4f128& v) const;
		Point4f128 operator+(const Point4f128& p) const;
		
		Point4f128& operator+=(const Vector4f128& v);
		Point4f128& operator+=(const Point4f128& p);

		Vector4f128 operator-(const Point4f128& p);
		Point4f128 operator-(const Vector4f128& v) const;
		Point4f128& operator-=(const Vector4f128& v);

		Point4f128 operator*(float mult) const;
		Point4f128& operator*=(float mult);

		Point4f128 operator/(float div) const;
		Point4f128& operator/=(float div);

		float operator[](uint32_t x) const;

	private:
		Point4f128(__m128 value);
		__m128 m_Value;
	};

	Point4f128 operator*(float f, const Point4f128& v);
}

