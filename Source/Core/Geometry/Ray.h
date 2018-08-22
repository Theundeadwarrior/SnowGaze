#pragma once

#include "Core/Core.h"

#include "Core/Geometry/Point.h"
#include "Core/Geometry/Vector.h"

#include <limits>

namespace SnowGaze
{
	class Ray
	{
	public:
		Ray();
		~Ray() = default;
		Ray(const Point3f& origin, const Vec3f& direction, float start, float end = std::numeric_limits<float>::infinity(), float time = 0.0f, int depth = 0);
		Ray(const Point3f& origin, const Vec3f& direction, const Ray& parent, float start, float end = std::numeric_limits<float>::infinity());

		Point3f operator()(float t);

	public:
		Point3f o;
		Vec3f d;

		mutable float mint;
		mutable float maxt;

		float time;
		int depth; // How many bounces
	};

	class RayDifferential : public Ray
	{
	public:
		RayDifferential();
		RayDifferential(const Point3f& origin, const Vec3f& direction, float start, float end = std::numeric_limits<float>::infinity(), float time = 0.0f, int depth = 0);
		RayDifferential(const Point3f& origin, const Vec3f& direction, const Ray& parent, float start, float end = std::numeric_limits<float>::infinity());

		void ScaleDifferentials(float s);

	public:
		Point3f rxOrigin;
		Point3f ryOrigin;
		Vec3f rxDirection;
		Vec3f ryDirection;
		bool m_HasDifferential;
	};
}
