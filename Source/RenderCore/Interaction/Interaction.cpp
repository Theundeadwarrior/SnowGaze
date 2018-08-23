#include "RenderCore/Interaction/Interaction.h"


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
		, m_WorldObject(wo)
		, m_Time(time)
		//, m_Medium(mediumInterface)
	{
	}
}
