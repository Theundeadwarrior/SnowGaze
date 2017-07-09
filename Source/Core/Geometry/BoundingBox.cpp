#include "BoundingBox.h"

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


