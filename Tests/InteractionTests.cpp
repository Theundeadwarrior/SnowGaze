#include <catch.hpp>

#include "Core/Geometry/Transform.h"
#include "RenderCore/Interaction/Interaction.h"

using namespace SnowGaze;

TEST_CASE("Testing Transform on Interactions")
{
	SurfaceInteraction s;
	Transform t;
	auto s2 = t(s);
}