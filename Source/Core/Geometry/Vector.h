#pragma once

#include "Core/Core.h"

#if USING( INTEL_INTRINSICS )
#include "Core/Geometry/Vector/Vectorf128.h"
namespace Core
{
	using Vec3f = Vector4f128;
}
#else
#include "Core/Geometry/Vector/Vector4f.h"
namespace Core
{
	using Vec3f = Vector3<float>;
}
#endif 

