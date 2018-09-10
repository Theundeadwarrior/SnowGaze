#pragma once

#include "Core/Core.h"

#include "Core/Geometry/Geometry.h"
#include "Core/Geometry/Math.h"
#include "Core/Geometry/Vector.h"

#include <assert.h>
#include <limits>


namespace SnowGaze
{
	template<typename T>
	Bounds3<T>::Bounds3()
		: m_Min(std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity())
		, m_Max(-std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::infinity())
	{}

	template<typename T>
	Bounds3<T>::Bounds3(const Point3<T>& p)
		: m_Min(p)
		, m_Max(p)
	{}

	template<typename T>
	Bounds3<T>::Bounds3(const Point3<T>& p1, const Point3<T>& p2)
	{
		m_Min = Point3<T>(fmin(p1.x, p2.x), fmin(p1.y, p2.y), fmin(p1.z, p2.z));
		m_Max = Point3<T>(fmax(p1.x, p2.x), fmax(p1.y, p2.y), fmax(p1.z, p2.z));

	}

	template<typename T>
	bool Bounds3<T>::IsOverlapping(const Bounds3& rhs) const
	{
		bool isOverlappingX = (m_Max.x >= rhs.m_Min.x) && (rhs.m_Max.x >= m_Min.x);
		bool isOverlappingY = (m_Max.y >= rhs.m_Min.y) && (rhs.m_Max.y >= m_Min.y);
		bool isOverlappingZ = (m_Max.z >= rhs.m_Min.z) && (rhs.m_Max.z >= m_Min.z);
		return isOverlappingX && isOverlappingY && isOverlappingZ;
	}

	template<typename T>
	template<typename U>
	void Bounds3<T>::Expand(U f)
	{
		m_Min -= Vector3<T>(f, f, f);
		m_Max += Vector3<T>(f, f, f);
	}

	template<typename T>
	float Bounds3<T>::GetSurfaceArea() const
	{
		Vector3<T> d = m_Max - m_Min;
		return 2.0f * (d.x * d.y + d.y * d.z + d.x * d.z);
	}

	template<typename T>
	T Bounds3<T>::GetVolume() const
	{
		Vector3<T> d = m_Max - m_Min;
		return d.x * d.y * d.z;
	}

	template<typename T>
	int Bounds3<T>::GetMaximumExtend() const
	{
		Vector3<T> d = m_Max - m_Min;
		if (d.x > d.y && d.x > d.z)
			return 0;
		else if (d.y > d.z)
			return 1;
		return 2;
	}

	template<typename T>
	Point3<T> Bounds3<T>::GetLerp(float x, float y, float z) const
	{
		return Point3<T>(Math::GetLerp(x, m_Min.x, m_Max.x), Math::GetLerp(y, m_Min.y, m_Max.y), Math::GetLerp(z, m_Min.z, m_Max.z));
	}

	template<typename T>
	Vector3<T> Bounds3<T>::GetOffset(const Point3<T>& p) const
	{
		return Vector3<T>((p.x - m_Min.x) / (m_Max.x - m_Min.x),
			(p.y - m_Min.y) / (m_Max.y - m_Min.y),
			(p.z - m_Min.z) / (m_Max.z - m_Min.z));
	}

	template<typename T>
	void Bounds3<T>::GetBoundingSphere(Point3<T>* center, float * radius) const
	{
		*center = 0.5f * m_Min + 0.5f * m_Max;
		*radius = IsInside(*center, *this) ? Geometry::Distance(*center, m_Max) : 0;
	}

	template<typename T>
	const Point3<T>& Bounds3<T>::operator[](int i) const
	{
		assert(i >= 0 && i < 2);
		if (i == 0)
			return m_Min;
		return m_Max;
	}

	template<typename T>
	Point3<T> & Bounds3<T>::operator[](int i)
	{
		assert(i >= 0 && i < 2);
		if (i == 0)
			return m_Min;
		return m_Max;
	}

	template<typename T>
	bool IsInside(const Point3<T>& p, const Bounds3<T>& bbox)
	{
		return(p.x >= bbox.m_Min.x && p.x <= bbox.m_Max.x &&
			p.y >= bbox.m_Min.y && p.y <= bbox.m_Max.y &&
			p.z >= bbox.m_Min.z && p.z <= bbox.m_Max.z);
	}

	template<typename T>
	bool IsInsideExclusive(const Point3<T>& p, const Bounds3<T>& bbox)
	{
		return(p.x > bbox.m_Min.x && p.x < bbox.m_Max.x &&
			p.y > bbox.m_Min.y && p.y < bbox.m_Max.y &&
			p.z > bbox.m_Min.z && p.z < bbox.m_Max.z);
	}

	template<typename T>
	Bounds3<T> Union(const Bounds3<T> & b, const Point3<T> & p)
	{
		Bounds3<T> ret = b;
		ret.m_Min.x = fmin(b.m_Min.x, p.x);
		ret.m_Min.y = fmin(b.m_Min.y, p.y);
		ret.m_Min.z = fmin(b.m_Min.z, p.z);
		ret.m_Max.x = fmax(b.m_Max.x, p.x);
		ret.m_Max.y = fmax(b.m_Max.y, p.y);
		ret.m_Max.z = fmax(b.m_Max.z, p.z);
		return ret;
	}

	template<typename T>
	Bounds3<T> Union(const Bounds3<T>& b1, const Bounds3<T>& b2)
	{
		Bounds3<T> ret = b1;
		ret.m_Min.x = fmin(b1.m_Min.x, b2.m_Min.x);
		ret.m_Min.y = fmin(b1.m_Min.y, b2.m_Min.y);
		ret.m_Min.z = fmin(b1.m_Min.z, b2.m_Min.z);
		ret.m_Max.x = fmax(b1.m_Max.x, b2.m_Max.x);
		ret.m_Max.y = fmax(b1.m_Max.y, b2.m_Max.y);
		ret.m_Max.z = fmax(b1.m_Max.z, b2.m_Max.z);
		return ret;
	}

	template <typename T>
	inline bool Bounds3<T>::IntersectP(const Ray &ray, float *hitt0, float *hitt1) const
	{
		float t0 = 0, t1 = ray.tMax;
		for (int i = 0; i < 3; ++i) {
			// Update interval for _i_th bounding box slab
			float invRayDir = 1 / ray.d[i];
			float tNear = (pMin[i] - ray.o[i]) * invRayDir;
			float tFar = (pMax[i] - ray.o[i]) * invRayDir;

			// Update parametric interval from slab intersection $t$ values
			if (tNear > tFar) std::swap(tNear, tFar);

			// Update _tFar_ to ensure robust ray--bounds intersection
			tFar *= 1 + 2 * Gamma(3);
			t0 = tNear > t0 ? tNear : t0;
			t1 = tFar < t1 ? tFar : t1;
			if (t0 > t1) return false;
		}
		if (hitt0) *hitt0 = t0;
		if (hitt1) *hitt1 = t1;
		return true;
	}
}
