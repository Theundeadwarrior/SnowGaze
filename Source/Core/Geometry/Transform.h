#pragma once

#include "Core/Geometry/Matrix.h"
#include "Core/Geometry/Quaternion.h"

#include <memory>

namespace SnowGaze { 
	template<typename T> class Vector3;
	template<typename T> class Point3;
	template<typename T> class Normal3;
	template<typename T> class Bounds3;
	class Ray;
	class RayDifferential;
	class SurfaceInteraction;
}

namespace SnowGaze
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
		template<typename T>
		Point3<T> operator()(const Point3<T>& p) const; // TODO: see if we could use move to return this.

		template<typename T>
		Vector3<T> operator()(const Vector3<T>& v) const;

		template<typename T>
		Normal3<T> operator()(const Normal3<T>& n) const;

		template<typename T>
		Bounds3<T> operator()(const Bounds3<T>& b) const;

		Ray operator()(const Ray& r) const;
		RayDifferential operator()(const RayDifferential & r) const;
		Transform operator*(const Transform& t2) const;
		SurfaceInteraction operator()(const SurfaceInteraction& s) const;

		template<typename T>
		Point3<T> operator()(const Point3<T>& p, Vector3<T>& absError) const;

		template<typename T>
		Vector3<T> operator()(const Vector3<T>& v, Vector3<T>& absError) const;

		template <typename T>
		Point3<T> operator()(const Point3<T> &p, const Vector3<T> &pError, Vector3<T> *pTransError) const;

		template<typename T>
		Ray operator()(const Ray& r, Vector3<T>& originError, Vector3<T>& directionError) const;

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

	template<typename T>
	Point3<T> Transform::operator()(const Point3<T>& p) const
	{
		float x = p.x, y = p.y, z = p.z;
		float xp = m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z + m.m[0][3];
		float yp = m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z + m.m[1][3];
		float zp = m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z + m.m[2][3];
		float wp = m.m[3][0] * x + m.m[3][1] * y + m.m[3][2] * z + m.m[3][3];
		if (wp == 1.0f)
			return Point3<T>(xp, yp, zp);
		else
			return Point3<T>(xp, yp, zp) / wp;
	}

	template<typename T>
	Vector3<T> Transform::operator()(const Vector3<T>& v) const
	{
		float x = v.x;
		float y = v.y;
		float z = v.z;
		return Vector3<T>(m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z,
			m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z,
			m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z);
	}

	template<typename T>
	Normal3<T> Transform::operator()(const Normal3<T> & n) const
	{
		float x = n.x;
		float y = n.y;
		float z = n.z;
		return Normal3<T>(m_Inv.m[0][0] * x + m_Inv.m[1][0] * y + m_Inv.m[2][0] * z,
			m_Inv.m[0][1] * x + m_Inv.m[1][1] * y + m_Inv.m[2][1] * z,
			m_Inv.m[0][2] * x + m_Inv.m[1][2] * y + m_Inv.m[2][2] * z);
	}

	template<typename T>
	Bounds3<T> Transform::operator()(const Bounds3<T> & b) const
	{
		const Transform &m = *this;
		Bounds3<T> result(m(Point3f(b.m_Min.x, b.m_Min.y, b.m_Min.z)));
		result = Union(result, m(Point3f(b.m_Max.x, b.m_Min.y, b.m_Min.z)));
		result = Union(result, m(Point3f(b.m_Min.x, b.m_Max.y, b.m_Min.z)));
		result = Union(result, m(Point3f(b.m_Min.x, b.m_Min.y, b.m_Max.z)));
		result = Union(result, m(Point3f(b.m_Min.x, b.m_Max.y, b.m_Max.z)));
		result = Union(result, m(Point3f(b.m_Max.x, b.m_Max.y, b.m_Min.z)));
		result = Union(result, m(Point3f(b.m_Max.x, b.m_Min.y, b.m_Max.z)));
		result = Union(result, m(Point3f(b.m_Max.x, b.m_Max.y, b.m_Max.z)));
		return result;
	}

	template<typename T>
	inline Point3<T> Transform::operator()(const Point3<T>& p, Vector3<T>& absError) const
	{
		T x = p.x, y = p.y, z = p.z;
		// Compute transformed coordinates from point _pt_
		T xp = m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z + m.m[0][3];
		T yp = m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z + m.m[1][3];
		T zp = m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z + m.m[2][3];
		T wp = m.m[3][0] * x + m.m[3][1] * y + m.m[3][2] * z + m.m[3][3];

		// Compute absolute error for transformed point
		T xAbsSum = (std::abs(m.m[0][0] * x) + std::abs(m.m[0][1] * y) +
			std::abs(m.m[0][2] * z) + std::abs(m.m[0][3]));
		T yAbsSum = (std::abs(m.m[1][0] * x) + std::abs(m.m[1][1] * y) +
			std::abs(m.m[1][2] * z) + std::abs(m.m[1][3]));
		T zAbsSum = (std::abs(m.m[2][0] * x) + std::abs(m.m[2][1] * y) +
			std::abs(m.m[2][2] * z) + std::abs(m.m[2][3]));
		
		absError = Gamma(3) * Vector3<T>(xAbsSum, yAbsSum, zAbsSum);
		
		assert(wp != 0);
		if (wp == 1)
			return Point3<T>(xp, yp, zp);
		else
			return Point3<T>(xp, yp, zp) / wp;
	}

	template<typename T>
	inline Vector3<T> Transform::operator()(const Vector3<T>& v, Vector3<T>& absError) const
	{
		T x = v.x, y = v.y, z = v.z;
		absError.x = Gamma(3) * (std::abs(m.m[0][0] * v.x) + std::abs(m.m[0][1] * v.y) + std::abs(m.m[0][2] * v.z));
		absError.y = Gamma(3) * (std::abs(m.m[1][0] * v.x) + std::abs(m.m[1][1] * v.y) + std::abs(m.m[1][2] * v.z));
		absError.z = Gamma(3) * (std::abs(m.m[2][0] * v.x) + std::abs(m.m[2][1] * v.y) + std::abs(m.m[2][2] * v.z));
		return Vector3<T>(m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z,
			m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z,
			m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z);
	}

	template <typename T>
	inline Point3<T> Transform::operator()(const Point3<T> &p, const Vector3<T> &ptError, Vector3<T> *absError) const
	{
		T x = p.x, y = p.y, z = p.z;
		T xp = m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z + m.m[0][3];
		T yp = m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z + m.m[1][3];
		T zp = m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z + m.m[2][3];
		T wp = m.m[3][0] * x + m.m[3][1] * y + m.m[3][2] * z + m.m[3][3];

		absError->x =
			(Gamma(3) + (T)1) *
			(std::abs(m.m[0][0]) * ptError.x + std::abs(m.m[0][1]) * ptError.y +
			std::abs(m.m[0][2]) * ptError.z) +
			Gamma(3) * (std::abs(m.m[0][0] * x) + std::abs(m.m[0][1] * y) +
			std::abs(m.m[0][2] * z) + std::abs(m.m[0][3]));
		absError->y =
			(Gamma(3) + (T)1) *
			(std::abs(m.m[1][0]) * ptError.x + std::abs(m.m[1][1]) * ptError.y +
			std::abs(m.m[1][2]) * ptError.z) +
			Gamma(3) * (std::abs(m.m[1][0] * x) + std::abs(m.m[1][1] * y) +
			std::abs(m.m[1][2] * z) + std::abs(m.m[1][3]));
		absError->z =
			(Gamma(3) + (T)1) *
			(std::abs(m.m[2][0]) * ptError.x + std::abs(m.m[2][1]) * ptError.y +
			std::abs(m.m[2][2]) * ptError.z) +
			Gamma(3) * (std::abs(m.m[2][0] * x) + std::abs(m.m[2][1] * y) +
			std::abs(m.m[2][2] * z) + std::abs(m.m[2][3]));

		assert(wp != 0);

		if (wp == 1.)
			return Point3<T>(xp, yp, zp);
		else
			return Point3<T>(xp, yp, zp) / wp;
	}

	template<typename T>
	inline Ray Transform::operator()(const Ray & r, Vector3<T>& originError, Vector3<T>& directionError) const
	{
		Point3<T> o = (*this)(r.o, originError);
		Vector3<T> d = (*this)(r.d, directionError);
		float tMax = r.maxt;
		float lengthSquared = d.GetSquareLength();
		if (lengthSquared > 0) {
			float dt = Dot(Math::Abs(d), originError) / lengthSquared;
			o += d * dt;
		}
		return Ray(o, d, tMax, r.time, r.medium);
	}

	class AnimatedTransform 
	{
	public:
		AnimatedTransform(const std::shared_ptr<Transform>& t1, float time1, const std::shared_ptr<Transform>& t2, float time2);
		
		void Interpolate(float time, Transform& tranformOut) const;

		Ray operator()(const Ray &r) const;
		RayDifferential operator()(const RayDifferential& r) const;
		Point3<float> operator()(float time, const Point3<float>& p) const;
		Vector3<float> operator()(float time, const Vector3<float>& v) const;
		
		template<typename T>
		Bounds3<T> MotionBounds(const Bounds3<T>& b, bool useInverse) const;
		//BBox MotionBounds(const BBox& b) const;
		//BBox BoundPointMotion(const Point3<float> &p) const;

	private:
		Matrix4x4 m_Scale[2];
		Quaternion m_Rotation[2];
		Vector3f m_Translation[2];
		const std::shared_ptr<Transform> m_StartTransform;
		const std::shared_ptr<Transform> m_EndTransform;
		const float m_StartTime;
		const float m_EndTime;
		const bool m_IsAnimated;
		bool m_HasRotation;
	};

	void DecomposeMatrix(const Matrix4x4& m, Vector3<float>& translation, Quaternion& rotation, Matrix4x4& scale);
}
