#pragma once

#include "Core/Geometry/Vector.h"

namespace SnowGaze
{
	class Transform;

	class Quaternion
	{
	public:
		Quaternion();
		Quaternion(const Transform& t);
		~Quaternion() = default;

		Quaternion operator+(const Quaternion& rhs) const;
		Quaternion& operator+=(const Quaternion& rhs);

		Quaternion operator-(const Quaternion& rhs) const;
		Quaternion& operator-=(const Quaternion& rhs);

		Quaternion operator*(float f) const;
		Quaternion& operator*=(float f);

		Quaternion operator/(float f) const;
		Quaternion& operator/=(float f);

		Transform ToTransform() const;

	public:
		Vector3f v;
		float w;
	};

	Quaternion operator*(float f, const Quaternion& q);

	float Dot(const Quaternion& q1, const Quaternion& q2);
	Quaternion Normalize(const Quaternion& q);
	Quaternion Slerp(float f, const Quaternion& q1, const Quaternion& q2);
		
}
