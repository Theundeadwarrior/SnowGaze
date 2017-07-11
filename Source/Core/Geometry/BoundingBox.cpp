#include "BoundingBox.h"

#include "Core/Vector/Vector.h"

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

	bool BBox::IsInside(const Point3f & p) const
	{
		return(p.x >= m_Min.x && p.x <= m_Max.x &&
			p.y >= m_Min.y && p.y <= m_Max.y &&
			p.z >= m_Min.z && p.z <= m_Max.z);
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
	
	BBox Geometry::Union(const BBox & b, const Point3f & p)
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

	BBox Geometry::Union(const BBox& b1, const BBox& b2)
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


