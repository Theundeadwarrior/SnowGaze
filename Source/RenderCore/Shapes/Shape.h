#pragma once
#include "Core/Geometry/Transform.h"

using namespace Core;

namespace RenderCore
{
	class Shape
	{
	public:
		Shape(const Transform* objectToWorld, const Transform* worldToObject, bool reverseOrientation)
		: m_ObjectToWorld(objectToWorld)
		, m_WorldToObject(worldToObject)
		, m_IsReverseOrientation(reverseOrientation)
		, m_TransformSwapsHandedness(objectToWorld->HasSwappedHandedness())
		{
		}

	private:
		const Transform* m_ObjectToWorld;
		const Transform* m_WorldToObject;
		const bool m_IsReverseOrientation;
		const bool m_TransformSwapsHandedness;
	};
}