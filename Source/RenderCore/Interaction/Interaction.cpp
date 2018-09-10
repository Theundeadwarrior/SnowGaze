#include "..\..\Core\Geometry\Transform.h"
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
		SurfaceInteraction ret;
		ret.m_Point = (*this)(si.m_Point, si.m_Error, &ret.m_Error);

		// Transform remaining members of _SurfaceInteraction_
		const Transform &t = *this;
		ret.m_Normal = (t(si.m_Normal)).Normalize();
		ret.m_OutDir = (t(si.m_OutDir)).Normalize();
		ret.m_Time = si.m_Time;
		//ret.m_Medium = si.m_Medium;
		ret.m_Uv = si.m_Uv;
		ret.m_Shape = si.m_Shape;
		ret.m_Dpdu = t(si.m_Dpdu);
		ret.m_Dpdv = t(si.m_Dpdv);
		ret.m_Dndu = t(si.m_Dndu);
		ret.m_Dndv = t(si.m_Dndv);
		ret.m_Shading.n = (t(si.m_Shading.n)).Normalize();
		ret.m_Shading.dpdu = t(si.m_Shading.dpdu);
		ret.m_Shading.dpdv = t(si.m_Shading.dpdv);
		ret.m_Shading.dndu = t(si.m_Shading.dndu);
		ret.m_Shading.dndv = t(si.m_Shading.dndv);
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
		ret.m_Shading.n = Geometry::FaceForward(ret.m_Shading.n, ret.m_Normal);
		//ret.faceIndex = si.faceIndex;
		return ret;
	}
}
