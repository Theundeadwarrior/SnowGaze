#pragma once

#include <stdint.h>

#include "Core/Geometry/Normal.h"
#include "Core/Geometry/Point.h"
#include "Core/Geometry/Vector.h"


namespace SnowGaze
{
	class Interaction
	{
	public:
		Interaction();
		Interaction(const Point3<float>& p, const Normal3<float>& n, const Vector3<float>& error,
			const Vector3<float>& wo, float time);//, const MediumInterface& mediumInteface);


	private:
		Point3f m_Point;
		float m_Time;
		Vector3f m_Error;
		Vector3f m_WorldObject;
		Normal3f m_Normal;
		//MediumInterface m_Interface;
	};
}