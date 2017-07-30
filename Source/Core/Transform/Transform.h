#pragma once

#include "Core/Math/Matrix.h"

namespace Core { 
	template<typename T> class Vector3;
	template<typename T> class Point3;
	class BBox;
	class Normal;
	class Ray;
}

namespace Core
{
	class Transform
	{
	public:
		Transform() = default;
		Transform(float mat[4][4]);
		Transform(const Matrix4x4& mat);
		Transform(const Matrix4x4& mat, const Matrix4x4& mat_inverse);
		~Transform() = default;

		friend Transform GetInverse(const Transform& t);

		// Applying transforms
		Point3<float> operator()(const Point3<float>& p) const; // TODO: see if we could use move to return this.
		Vector3<float> operator()(const Vector3<float>& v) const;
		Normal operator()(const Normal& n) const;
		Ray operator()(const Ray& r) const;
		BBox operator()(const BBox& b) const;

		Transform operator*(const Transform& t2) const;

		bool IsIdentify() const;
		bool HasScaling() const;
		bool HasSwappedHandedness() const;

	private:
		Matrix4x4 m;
		Matrix4x4 m_Inv;

		friend class Quaternion;
	};

	// Build transformations
	Transform GetTranslate(const Vector3<float>& delta);
	Transform GetScale(float x, float y, float z);
	Transform GetRotateX(float angle);
	Transform GetRotateY(float angle);
	Transform GetRotateZ(float angle);
	Transform GetRotate(float angle, const Vector3<float>& axis);
	Transform GetLookAt(const Point3<float>& pos, const Point3<float>& look, const Vector3<float>& up);

	class AnimatedTransform 
	{
	public:
		AnimatedTransform(const Transform& t1, float time1, const Transform& t2, float time2);

	};
}
