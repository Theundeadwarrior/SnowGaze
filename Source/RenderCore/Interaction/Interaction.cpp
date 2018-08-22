#include "RenderCore/Interaction/Interaction.h"


namespace SnowGaze
{
	Interaction::Interaction() 
		: m_Time(0.0f) 
	{
	}

	Interaction::Interaction(const Point3<float>& p, const Normal & n, const Vector3<float>& error, const Vector3<float>& wo, float time)// , const MediumInterface & mediumInterface)
		: m_Point(p)
		, m_Normal(n)
		, m_Error(error)
		, m_WorldObject(wo)
		, m_Time(time)
		//, m_Medium(mediumInterface)
	{
	}
}
