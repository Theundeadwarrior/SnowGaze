#pragma once

#include "Core/Geometry/Matrix.h"
#include "Core/Geometry/Quaternion.h"

#include <memory>

namespace Core { 
	template<typename T> class Vector3;
	template<typename T> class Point3;
	class BBox;
	class Normal;
	class Ray;
	class RayDifferential;
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
		RayDifferential operator()(const RayDifferential & r) const;
		BBox operator()(const BBox& b) const;

		Transform operator*(const Transform& t2) const;

		bool IsIdentify() const;
		bool HasScaling() const;
		bool HasSwappedHandedness() const;

		const Matrix4x4& GetMatrix() const { return m; }

	private:
		Matrix4x4 m;
		Matrix4x4 m_Inv;

		friend class Quaternion;
		friend class AnimatedTransform;
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
		AnimatedTransform(const std::shared_ptr<Transform>& t1, float time1, const std::shared_ptr<Transform>& t2, float time2);
		
		void Interpolate(float time, Transform& tranformOut) const;

		Ray operator()(const Ray &r) const;
		RayDifferential operator()(const RayDifferential& r) const;
		Point3<float> operator()(float time, const Point3<float>& p) const;
		Vector3<float> operator()(float time, const Vector3<float>& v) const;
		
		BBox MotionBounds(const BBox& b, bool useInverse) const;
		//BBox MotionBounds(const BBox& b) const;
		//BBox BoundPointMotion(const Point3<float> &p) const;

	private:
		Matrix4x4 m_Scale[2];
		Quaternion m_Rotation[2];
		Vec3f m_Translation[2];
		const std::shared_ptr<Transform> m_StartTransform;
		const std::shared_ptr<Transform> m_EndTransform;
		const float m_StartTime;
		const float m_EndTime;
		const bool m_IsAnimated;
		bool m_HasRotation;
	};

	void DecomposeMatrix(const Matrix4x4& m, Vector3<float>& translation, Quaternion& rotation, Matrix4x4& scale);
}
