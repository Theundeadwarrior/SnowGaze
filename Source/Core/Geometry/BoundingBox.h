#pragma once

#include "Core/Geometry/Point.h"

namespace Core { template<typename T> class Vector3; }

namespace Core
{
	class BBox
	{
	public:
		BBox();
		BBox(const Point3f& p);
		BBox(const Point3f& p1, const Point3f& p2);
		~BBox() = default;

		bool IsOverlapping(const BBox& rhs) const;

		void Expand(float f); // expands the box by padding it by f on every sides.

		float GetSurfaceArea() const;
		float GetVolume() const;

		int GetMaximumExtend() const;
		Point3f GetLerp(float x, float y, float z) const;
		Vector3<float> GetOffset(const Point3f& p) const;
		void GetBoundingSphere(Point3f* center, float* radius) const;

		const Point3f& operator[](int i) const;
		Point3f& operator[](int i);

	public:
		Point3f m_Min;
		Point3f m_Max;
	};

	bool IsInside(const Point3f& p, const BBox& bbox);
	bool IsInsideExclusive(const Point3f& p, const BBox& bbox);
	BBox Union(const BBox& b, const Point3f& p);
	BBox Union(const BBox& b1, const BBox& b2);
}

