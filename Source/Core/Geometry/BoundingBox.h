#pragma once

#include "Core/Geometry/Point.h"

namespace SnowGaze { template<typename T> class Vector3; }

namespace SnowGaze
{
	template<typename T>
	class Bounds3
	{
	public:
		Bounds3();
		
		Bounds3(const Point3<T>& p);

		Bounds3(const Point3<T>& p1, const Point3<T>& p2);

		~Bounds3() = default;

		bool IsOverlapping(const Bounds3& rhs) const;

		template<typename U>
		void Expand(U f); // expands the box by padding it by f on every sides.

		float GetSurfaceArea() const;
		T GetVolume() const;

		int GetMaximumExtend() const;
		Point3<T> GetLerp(float x, float y, float z) const;
		Vector3<T> GetOffset(const Point3<T>& p) const;
		void GetBoundingSphere(Point3<T>* center, float* radius) const;

		const Point3<T>& operator[](int i) const;
		Point3<T>& operator[](int i);

	public:
		Point3<T> m_Min;
		Point3<T> m_Max;
	};

	template<typename T>
	bool IsInside(const Point3<T>& p, const Bounds3<T>& bbox);

	template<typename T>
	bool IsInsideExclusive(const Point3<T>& p, const Bounds3<T>& bbox);

	template<typename T>
	Bounds3<T> Union(const Bounds3<T>& b, const Point3<T>& p);

	template<typename T>
	Bounds3<T> Union(const Bounds3<T>& b1, const Bounds3<T>& b2);

	using Bounds3f = Bounds3<float>;
	using Bounds3i = Bounds3<int>;
}

#include "Core/Geometry/BoundingBox.hpp"
