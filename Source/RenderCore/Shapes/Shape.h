#pragma once

#include <stdint.h>


namespace SnowGaze
{
	class Transform;
	class SurfaceInteraction;
	class Ray;
	class Interaction;
	template<typename T> class Point2;
	template<typename T> class Point3;
	template<typename T> class Vector3;
	template<typename T> class Bounds3;

	class Shape
	{
	public:
		Shape(const Transform* objectToWorld, const Transform* worldToObject, bool reverseOrientation);
		virtual ~Shape() {};

		virtual Bounds3<float> GetObjectBound() const = 0;
		virtual Bounds3<float> GetWorldBound() const;

		virtual bool Intersect(const Ray& ray, float* hit, SurfaceInteraction* isect, bool testAlphaTexture = true) const = 0;
		virtual bool IntersectP(const Ray& ray, bool testAlphaTexture = true) const
		{
			return Intersect(ray, nullptr, nullptr, testAlphaTexture);
		}

		virtual float GetArea() const = 0;
		
		virtual Interaction Sample(const Point2<float>& u, float* pdf) const = 0;
		//virtual float PDF(const Interaction&) const { return 1 / GetArea(); }

		//virtual Interaction Sample(const Interaction& ref, const Point2<float>& u, float* pdf) const;
		//virtual float PDF(const Interaction& ref, const Vector3<float>& wi) const;

		//virtual float GetSolidAngle(const Point3<float>& p, int nbSample = 512) const;

		bool GetIsReverseOrientation() const { return m_IsReverseOrientation; }
		bool GetTransformSwapsHandedness() const { return m_TransformSwapsHandedness; }


		static uint32_t s_ShapeCount;

	protected:
		const Transform* m_ObjectToWorld;
		const Transform* m_WorldToObject;
		const bool m_IsReverseOrientation;
		const bool m_TransformSwapsHandedness;
		const uint32_t m_ShapeId;
	};
}