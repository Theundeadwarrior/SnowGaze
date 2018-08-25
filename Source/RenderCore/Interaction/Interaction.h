#pragma once

#include <stdint.h>

#include "Core/Geometry/Normal.h"
#include "Core/Geometry/Point.h"
#include "Core/Geometry/Vector.h"

namespace SnowGaze
{
	class Shape;
	class Transform;

	class Interaction
	{
	public:
		Interaction();
		Interaction(const Point3f& p, const Normal3f& n, const Vector3f& error,
			const Vector3f& wo, float time);//, const MediumInterface& mediumInteface);

		bool IsSurfaceInteraction() const;


	public:
		//MediumInterface m_Interface;
		Point3f m_Point;
		Vector3f m_Error;
		Vector3f m_OutDir;
		Normal3f m_Normal;
		float m_Time;
	};

	class SurfaceInteraction : public Interaction
	{
	public:
		struct Shading
		{
			Normal3f n;
			Vector3f dpdu;
			Vector3f dpdv;
			Normal3f dndu;
			Normal3f dndv;
		};

	public:
		SurfaceInteraction() {}
		SurfaceInteraction(const Point3f& p, const Vector3f& error, const Point2f& uv, const Vector3f& wo, 
			const Vector3f& dpdu, const Vector3f& dpdv, const Normal3f& dndu, const Normal3f& dndv,
			float time, const Shape* shape);

		void SetShadingGeometry(const Vector3f &dpdu, const Vector3f &dpdv, const Normal3f &dndu, const Normal3f &dndv, bool orientationIsAuthoritative);

	public:
		Shading m_Shading;
		const Shape* m_Shape = nullptr;
		Vector3f m_Dpdu;
		Vector3f m_Dpdv;
		Normal3f m_Dndu;
		Normal3f m_Dndv;
		Point2f m_Uv;
	};
}