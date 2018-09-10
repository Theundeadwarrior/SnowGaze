#include "Ray.h"

#include <limits>

namespace SnowGaze
{
	Ray::Ray() 
		: maxt(std::numeric_limits<float>::infinity())
		, time(0.0f)
		, medium(nullptr) 
	{}

	Ray::Ray(const Point3f & o, const Vector3f & d, float tMax, float time, const Medium * medium)
		: o(o)
		, d(d)
		, maxt(tMax)
		, time(time)
		, medium(medium) 
	{}

	Point3f Ray::operator()(float t) const
	{
		return o + d * t;
	}

	RayDifferential::RayDifferential()
		: m_HasDifferential(false)
	{}

	RayDifferential::RayDifferential(const Point3f & origin, const Vector3f & direction, float tMax, float time, const Medium* medium)
		: Ray(origin, direction, tMax, time, medium)
		, m_HasDifferential(false)
	{}

	void RayDifferential::ScaleDifferentials(float s)
	{
		rxOrigin = o + (rxOrigin - o) * s;
		ryOrigin = o + (ryOrigin - o) * s;
		rxDirection = d + (rxDirection - d) * s;
		ryDirection = d + (ryDirection - d) * s;
	}
}
