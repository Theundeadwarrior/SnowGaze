#pragma once

#include <nmmintrin.h>
#include <inttypes.h>

namespace Core
{
	class Transform;

	class Quaternion4f128
	{
	public:
		Quaternion4f128();
		Quaternion4f128(__m128 value);
		Quaternion4f128(const Transform& t);
		~Quaternion4f128() = default;

		__m128 GetValue() const { return m_Value; }
		
		Quaternion4f128 operator+(const Quaternion4f128& rhs) const;
		Quaternion4f128& operator+=(const Quaternion4f128& rhs);

		Quaternion4f128 operator-(const Quaternion4f128& rhs) const;
		Quaternion4f128& operator-=(const Quaternion4f128& rhs);

		Quaternion4f128 operator*(float f) const;
		Quaternion4f128& operator*=(float f);

		Quaternion4f128 operator/(float f) const;
		Quaternion4f128& operator/=(float f);

		Transform ToTransform() const;

	private:
		__m128 m_Value;
	};

	Quaternion4f128 operator*(float f, const Quaternion4f128& v);

	float Dot(const Quaternion4f128& q1, const Quaternion4f128& q2);
	Quaternion4f128 Normalize(const Quaternion4f128& q);
	Quaternion4f128 Slerp(float t, const Quaternion4f128& q1, const Quaternion4f128& q2);
}

