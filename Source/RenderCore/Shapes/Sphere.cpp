#include "RenderCore/Shapes/Sphere.h"

#include "Core/Geometry/Math.h"

#include <algorithm>

namespace SnowGaze
{
	Sphere::Sphere(const Transform * objectToWorld, const Transform * worldToObject, bool reverseOrientation, float radius, float zMin, float zMax, float phiMax)
		: Shape(objectToWorld, worldToObject, reverseOrientation)
		, m_Radius(radius)
		, m_ZMin(Math::Clamp(std::min(zMin, zMax), -radius, radius))
		, m_ZMax(Math::Clamp(std::max(zMin, zMax), -radius, radius))
		, m_ThetaMin(std::acos(Math::Clamp(std::min(zMin, zMax) / radius, -1.0f, 1.0f)))
		, m_ThetaMax(std::acos(Math::Clamp(std::max(zMin, zMax) / radius, -1.0f, 1.0f)))
		, m_PhiMax(Radians(Math::Clamp(phiMax, 0.0f, 360.0f)))
	{
	}
}
