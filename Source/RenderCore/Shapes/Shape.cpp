#include "RenderCore/Shapes/Shape.h"

#include "Core/Geometry/BoundingBox.h"
#include "Core/Geometry/Transform.h"

namespace SnowGaze
{
	uint32_t Shape::s_ShapeCount = 1;

	inline Shape::Shape(const Transform * objectToWorld, const Transform * worldToObject, bool reverseOrientation)
		: m_ObjectToWorld(objectToWorld)
		, m_WorldToObject(worldToObject)
		, m_IsReverseOrientation(reverseOrientation)
		, m_TransformSwapsHandedness(objectToWorld->HasSwappedHandedness())
		, m_ShapeId(s_ShapeCount++)
	{
	}

	BBox Shape::GetWorldBound() const
	{
		return (*m_ObjectToWorld)(GetObjectBound());
	}
}
