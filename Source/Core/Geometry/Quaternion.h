#pragma once

#if USING( INTEL_INTRINSICS )
#include "Core/Geometry/Quaternion/Quaternionf128.h"
namespace Core
{
	using Quaternion = Quaternion4f128;
}

#else // #if USING( INTEL_INTRINSICS )
#include "Core/Geometry/Quaternion/Quaternion4f.h"
#endif // #else // #if USING( INTEL_INTRINSICS )
