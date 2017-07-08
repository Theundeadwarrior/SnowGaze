#include "Core/Geometry/Geometry.h"

#include "Core/Geometry/Normal.h"

namespace Core
{
	Normal Geometry::Normalize(const Normal& n)
	{
		return n / n.GetLength();
	}
}
