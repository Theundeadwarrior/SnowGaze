#pragma once

#include <stdint.h>
#include "RenderCore/Shapes/Shape.h"

namespace SnowGaze
{
	class Sphere : public Shape
	{
	public:
		Sphere(const Transform* objectToWorld, const Transform* worldToObject, bool reverseOrientation, float radius, float zMin, float zMax, float phiMax);

	private:
		const float m_Radius;
		const float m_ZMin;
		const float m_ZMax;
		const float m_ThetaMin;
		const float m_ThetaMax;
		const float m_PhiMax;
	};
}