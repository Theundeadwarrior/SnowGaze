#pragma once

#include <nmmintrin.h>
#include <inttypes.h>

namespace Core
{
	class Vector4f128
	{
	public:
		Vector4f128();
		Vector4f128(float x, float y, float z, float w);
		Vector4f128(float v);
		Vector4f128(__m128 value);
		~Vector4f128();

		float GetLength() const;
		float GetSquareLength() const;
		__m128 GetValue() const { return m_Value; }

		void Normalize();

		Vector4f128 operator+(const Vector4f128& lhs) const;
		Vector4f128& operator+=(const Vector4f128& lhs);

		Vector4f128 operator-(const Vector4f128& lhs) const;
		Vector4f128 operator-=(const Vector4f128& lhs);

		Vector4f128 operator*(float mult) const;
		Vector4f128& operator*=(float mult);

		Vector4f128 operator/(float div) const;
		Vector4f128& operator/=(float div);

		float operator[](uint32_t x) const;

	private:
		__m128 m_Value;
	};

	Vector4f128 operator*(float f, const Vector4f128& v);
}

