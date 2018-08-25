#include "RenderCore/Interaction/Interaction.h"

#include "Core/Geometry/Geometry.h"
#include "Core/Geometry/Normal.h"
#include "Core/Geometry/Transform.h"
#include "RenderCore/Shapes/Shape.h"

namespace SnowGaze
{
	Interaction::Interaction() 
		: m_Time(0.0f) 
	{
	}

	Interaction::Interaction(const Point3f& p, const Normal3f & n, const Vector3f& error, const Vector3f& wo, float time)// , const MediumInterface & mediumInterface)
		: m_Point(p)
		, m_Normal(n)
		, m_Error(error)
		, m_OutDir(wo)
		, m_Time(time)
		//, m_Medium(mediumInterface)
	{
	}

	bool Interaction::IsSurfaceInteraction() const
	{
		return m_Normal != Normal3f();
	}

	SurfaceInteraction::SurfaceInteraction(const Point3f & p, const Vector3f & error, const Point2f & uv, const Vector3f & wo, const Vector3f & dpdu, const Vector3f & dpdv, const Normal3f & dndu, const Normal3f & dndv, float time, const Shape * shape)
		: Interaction(p, Normal3f(Geometry::Normalize(Geometry::Cross(dpdu, dpdv))), error, wo, time)
		, m_Shape(shape)
		, m_Dpdu(dpdu)
		, m_Dpdv(dpdv)
		, m_Dndu(dndu)
		, m_Dndv(dndv)
		, m_Uv(uv)
	{
		m_Shading.n = m_Normal;
		m_Shading.dpdu = dpdu;
		m_Shading.dpdv = dpdv;
		m_Shading.dndu = dndu;
		m_Shading.dndv = dndv;

		if ((shape->GetIsReverseOrientation() && !shape->GetTransformSwapsHandedness()) ||
			!shape->GetIsReverseOrientation() && shape->GetTransformSwapsHandedness())
		{
			m_Normal *= -1;
			m_Shading.n *= -1;
		}
	}

	void SurfaceInteraction::SetShadingGeometry(const Vector3f & dpdu, const Vector3f & dpdv, const Normal3f & dndu, const Normal3f & dndv, bool orientationIsAuthoritative)
	{
		m_Shading.n = Geometry::Normalize((Normal3f)Geometry::Cross(dpdu, dpdv));
		if (m_Shape && (m_Shape->GetIsReverseOrientation() ^ m_Shape->GetTransformSwapsHandedness()))
			m_Shading.n *= -1;
		if (orientationIsAuthoritative)
			m_Normal = GetFaceForward(m_Normal, m_Shading.n);
		else
			m_Shading.n = GetFaceForward(m_Shading.n, m_Normal);

		m_Shading.dpdu = dpdu;
		m_Shading.dpdv = dpdv;
		m_Shading.dndu = dndu;
		m_Shading.dndv = dndv;
	}

	SurfaceInteraction Transform::operator()(const SurfaceInteraction & si) const
	{
		//SurfaceInteraction ret;
		////ret.m_Point = (*this)(si.m_Point, si.m_Error, &ret.m_Error);

		//// Transform remaining members of _SurfaceInteraction_
		//const Transform &t = *this;
		//ret.n = Normalize(t(si.n));
		//ret.wo = Normalize(t(si.wo));
		//ret.time = si.time;
		//ret.mediumInterface = si.mediumInterface;
		//ret.uv = si.uv;
		//ret.shape = si.shape;
		//ret.dpdu = t(si.dpdu);
		//ret.dpdv = t(si.dpdv);
		//ret.dndu = t(si.dndu);
		//ret.dndv = t(si.dndv);
		//ret.shading.n = Normalize(t(si.shading.n));
		//ret.shading.dpdu = t(si.shading.dpdu);
		//ret.shading.dpdv = t(si.shading.dpdv);
		//ret.shading.dndu = t(si.shading.dndu);
		//ret.shading.dndv = t(si.shading.dndv);
		//ret.dudx = si.dudx;
		//ret.dvdx = si.dvdx;
		//ret.dudy = si.dudy;
		//ret.dvdy = si.dvdy;
		//ret.dpdx = t(si.dpdx);
		//ret.dpdy = t(si.dpdy);
		//ret.bsdf = si.bsdf;
		//ret.bssrdf = si.bssrdf;
		//ret.primitive = si.primitive;
		////    ret.n = Faceforward(ret.n, ret.shading.n);
		//ret.shading.n = Faceforward(ret.shading.n, ret.n);
		//ret.faceIndex = si.faceIndex;
		//return ret;

		return SurfaceInteraction();
	}
}
