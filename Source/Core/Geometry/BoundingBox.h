#pragma once

#include "Core/Geometry/Point.h"

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
		bool IsInside(const Point3f& p) const;

		void Expand(float f); // expands the box by padding it by f on every sides.

		float GetSurfaceArea() const;
		float GetVolume() const;

	public:
		Point3f m_Min;
		Point3f m_Max;
	};

	namespace Geometry
	{
		// Move to BBox class maybe?
		BBox Union(const BBox& b, const Point3f& p);
		BBox Union(const BBox& b1, const BBox& b2);
	}
}

