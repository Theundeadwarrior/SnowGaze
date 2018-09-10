#include "RenderCore/Primitives/GeometricPrimitive.h"

#include "Core/Geometry/BoundingBox.h"

namespace SnowGaze
{
	Bounds3<float> GeometricPrimitive::WorldBound() const
	{
		return Bounds3<float>();
	}

	bool GeometricPrimitive::Intersect(const Ray & r, SurfaceInteraction *) const
	{
		return false;
	}

	bool GeometricPrimitive::IntersectP(const Ray & r) const
	{
		return false;
	}

}
