#pragma once

#include "RenderCore/Primitives/Primitive.h"
#include <memory>

namespace SnowGaze
{
	class Shape;

	class GeometricPrimitive : public Primitive
	{
	public:
		// Inherited via Primitive
		virtual Bounds3<float> WorldBound() const override;
		virtual bool Intersect(const Ray & r, SurfaceInteraction *) const override;
		virtual bool IntersectP(const Ray & r) const override;

	private:
		std::shared_ptr<Shape> m_Shape;
		//std::shared_ptr<Material> m_Material;
		//std::shared_ptr<AreaLight> m_AreaLight;
		//MediumInterface m_MediumInterface;
	};
}

