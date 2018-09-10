#pragma once

#include "Core/Core.h"

#include "Core/Geometry/Point.h"
#include "Core/Geometry/Vector.h"

#include <limits>

namespace SnowGaze
{
	class Medium;

	class Ray
	{
	public:
		Ray();
		Ray(const Point3f& o, const Vector3f& d, float tMax = std::numeric_limits<float>::infinity(), float time = 0.f, const Medium *medium = nullptr);

		Point3f operator()(float t) const;

	public:
		Point3f o;
		Vector3f d;

		mutable float maxt;
		float time;
		const Medium* medium;
	};

	class RayDifferential : public Ray
	{
	public:
		RayDifferential();
		RayDifferential(const Point3f & origin, const Vector3f & direction, float tMax, float time, const Medium* medium);

		void ScaleDifferentials(float s);

	public:
		Point3f rxOrigin;
		Point3f ryOrigin;
		Vector3f rxDirection;
		Vector3f ryDirection;
		bool m_HasDifferential;
	};
}
