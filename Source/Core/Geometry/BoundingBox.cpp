#include "BoundingBox.h"

#include "Core/Geometry/Geometry.h"
#include "Core/Geometry/Math.h"
#include "Core/Geometry/Vector.h"

#include <assert.h>
#include <limits>


namespace Core
{
	BBox::BBox()
		: m_Min(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity())
		, m_Max(-std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity())
	{}

	BBox::BBox(const Point3f & p)
		: m_Min(p)
		, m_Max(p)
	{}

	BBox::BBox(const Point3f & p1, const Point3f & p2)
	{
		m_Min = Point3f(fmin(p1.x, p2.x), fmin(p1.y, p2.y), fmin(p1.z, p2.z));
		m_Max = Point3f(fmax(p1.x, p2.x), fmax(p1.y, p2.y), fmax(p1.z, p2.z));
	}

	bool BBox::IsOverlapping(const BBox & rhs) const
	{
		bool isOverlappingX = (m_Max.x >= rhs.m_Min.x) && (rhs.m_Max.x >= m_Min.x);
		bool isOverlappingY = (m_Max.y >= rhs.m_Min.y) && (rhs.m_Max.y >= m_Min.y);
		bool isOverlappingZ = (m_Max.z >= rhs.m_Min.z) && (rhs.m_Max.z >= m_Min.z);
		return isOverlappingX && isOverlappingY && isOverlappingZ;
	}

	void BBox::Expand(float f)
	{
		m_Min -= Vec3f(f, f, f);
		m_Max += Vec3f(f, f, f);
	}

	float BBox::GetSurfaceArea() const
	{
		auto d = m_Max - m_Min;
		return 2.0f * (d.x * d.y + d.y * d.z + d.x * d.z);
	}

	float BBox::GetVolume() const
	{
		auto d = m_Max - m_Min;
		return d.x * d.y * d.z;
	}

	int BBox::GetMaximumExtend() const
	{
		Vec3f d = m_Max - m_Min;
		if (d.x > d.y && d.x > d.z)
			return 0;
		else if (d.y > d.z)
			return 1;
		return 2;
	}

	Point3f BBox::GetLerp(float x, float y, float z) const
	{
		return Point3f(Math::GetLerp(x, m_Min.x, m_Max.x), Math::GetLerp(y, m_Min.y, m_Max.y), Math::GetLerp(z, m_Min.z, m_Max.z));
	}

	Vec3f BBox::GetOffset(const Point3f& p) const
	{
		return Vec3f((p.x - m_Min.x) / (m_Max.x - m_Min.x),
					 (p.y - m_Min.y) / (m_Max.y - m_Min.y),
					 (p.z - m_Min.z) / (m_Max.z - m_Min.z));
	}

	void BBox::GetBoundingSphere(Point3f * center, float * radius) const
	{
		*center = 0.5f * m_Min + 0.5f * m_Max;
		*radius = IsInside(*center, *this) ? Geometry::Distance(*center, m_Max) : 0;
	}

	// todo: refactor to remove this...
	const Point3f & BBox::operator[](int i) const
	{
		assert(i >= 0 && i < 2);
		if (i == 0)
			return m_Min;
		return m_Max;
	}

	// todo: refactor to remove this...
	Point3f & BBox::operator[](int i)
	{
		assert(i >= 0 && i < 2);
		if (i == 0)
			return m_Min;
		return m_Max;
	}
	
	bool IsInside(const Point3f & p, const BBox & bbox)
	{
		return(p.x >= bbox.m_Min.x && p.x <= bbox.m_Max.x &&
			p.y >= bbox.m_Min.y && p.y <= bbox.m_Max.y &&
			p.z >= bbox.m_Min.z && p.z <= bbox.m_Max.z);
	}

	bool IsInsideExclusive(const Point3f & p, const BBox & bbox)
	{
		return(p.x > bbox.m_Min.x && p.x < bbox.m_Max.x &&
			p.y > bbox.m_Min.y && p.y < bbox.m_Max.y &&
			p.z > bbox.m_Min.z && p.z < bbox.m_Max.z);
	}

	BBox Union(const BBox & b, const Point3f & p)
	{
		BBox ret = b;
		ret.m_Min.x = fmin(b.m_Min.x, p.x);
		ret.m_Min.y = fmin(b.m_Min.y, p.y);
		ret.m_Min.z = fmin(b.m_Min.z, p.z);
		ret.m_Max.x = fmax(b.m_Max.x, p.x);
		ret.m_Max.y = fmax(b.m_Max.y, p.y);
		ret.m_Max.z = fmax(b.m_Max.z, p.z);
		return ret;
	}

	BBox Union(const BBox& b1, const BBox& b2)
	{
		BBox ret = b1;
		ret.m_Min.x = fmin(b1.m_Min.x, b2.m_Min.x);
		ret.m_Min.y = fmin(b1.m_Min.y, b2.m_Min.y);
		ret.m_Min.z = fmin(b1.m_Min.z, b2.m_Min.z);
		ret.m_Max.x = fmax(b1.m_Max.x, b2.m_Max.x);
		ret.m_Max.y = fmax(b1.m_Max.y, b2.m_Max.y);
		ret.m_Max.z = fmax(b1.m_Max.z, b2.m_Max.z);
		return ret;
	}
}


