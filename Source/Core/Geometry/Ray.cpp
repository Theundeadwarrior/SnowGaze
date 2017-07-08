#include "Ray.h"

#include <limits>

namespace Core
{
	Ray::Ray()
		: mint(0.0f)
		, maxt(std::numeric_limits<float>::infinity())
		, time(0.0f)
		, depth(0)
	{}

	Ray::Ray(const Point3f & origin, const Vec3f & direction, float start, float end, float t, int d)
		: o(origin)
		, d(direction)
		, mint(start)
		, maxt(end)
		, time(t)
		, depth(d)
	{}

	Ray::Ray(const Point3f & origin, const Vec3f & direction, const Ray & parent, float start, float end)
		: o(origin)
		, d(direction)
		, mint(start)
		, maxt(end)
		, time(parent.time)
		, depth(parent.depth + 1)
	{}

	Point3f Ray::operator()(float t)
	{
		return o + d * t;
	}

	RayDifferential::RayDifferential()
		: hasDifferential(false)
	{}

	RayDifferential::RayDifferential(const Point3f & origin, const Vec3f & direction, float start, float end, float time, int depth)
		: Ray(origin, direction, start, end, time, depth)
		, hasDifferential(false)
	{}

	RayDifferential::RayDifferential(const Point3f & origin, const Vec3f & direction, const Ray & parent, float start, float end)
		: Ray(origin, direction, parent, start, end)
		, hasDifferential(false)
	{}

	void RayDifferential::ScaleDifferentials(float s)
	{
		rxOrigin = o + (rxOrigin - o) * s;
		ryOrigin = o + (ryOrigin - o) * s;
		rxDirection = d + (rxDirection - d) * s;
		ryDirection = d + (ryDirection - d) * s;
	}
}
