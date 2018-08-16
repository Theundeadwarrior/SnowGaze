#pragma once

#include "Core/Core.h"

#if USING( INTEL_INTRINSICS )
#include "Core/Geometry/Point/Pointf128.h"
namespace Core 
{
	using Point3f = Point4f128;
}
#else // #if USING( INTEL_INTRINSICS )
#include "Core/Geometry/Point/Point4f.h"
namespace Core
{
	using Point3f = Point3<float>;
}
#endif // #else // #if USING( INTEL_INTRINSICS )
