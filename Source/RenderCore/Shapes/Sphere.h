#pragma once

#include <stdint.h>
#include "RenderCore/Shapes/Shape.h"

namespace SnowGaze
{
	template<typename T> class Bounds3;
	template<typename T> class Point3;
	class Ray;
	class ErrorFloat;

	class Sphere : public Shape
	{
	public:
		Sphere(const Transform* objectToWorld, const Transform* worldToObject, bool reverseOrientation, float radius, float zMin, float zMax, float phiMax);

		// Inherited via Shape
		virtual bool Intersect(const Ray & ray, float * hit, SurfaceInteraction * isect, bool testAlphaTexture) const override;
		virtual bool IntersectP(const Ray& ray, bool testAlphaTexture = true) const override;
		virtual float GetArea() const override;
		virtual Interaction Sample(const Point2<float>& u, float * pdf) const override;
		virtual Bounds3<float> GetObjectBound() const override;

	private:
		void ComputeHitPosAndPhi(Point3<float>& pointHit, float& phi, ErrorFloat tShapeHit, const Ray& ray) const;

	private:
		const float m_Radius;
		const float m_ZMin;
		const float m_ZMax;
		const float m_ThetaMin;
		const float m_ThetaMax;
		const float m_PhiMax;


	};
}