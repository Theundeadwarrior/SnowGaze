#pragma once

#include "Core/Geometry/Vector.h"

namespace Core
{
	class Transform;
}

namespace Core
{
	class Quaternion
	{
	public:
		Quaternion();
		Quaternion(const Transform& t);
		~Quaternion();

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
		Vec3f v;
		float w;
	};

	Quaternion operator*(float f, const Quaternion& q);

	float Dot(const Quaternion& q1, const Quaternion& q2);
	Quaternion Normalize(const Quaternion& q);
	Quaternion Slerp(float f, const Quaternion& q1, const Quaternion& q2);
		
}
