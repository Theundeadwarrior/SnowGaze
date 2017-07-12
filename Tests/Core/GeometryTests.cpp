#include "catch.hpp"

#include "Core/Geometry/Geometry.h"
#include "Core/Math/Vector.h"

using namespace Core;

TEST_CASE("Dot Product")
{
	Vec3f v1(1.0f, 0.0f, 0.0f);
	Normal n1(1.0f, 0.0f, 0.0f);

	REQUIRE(Geometry::Dot(v1, n1) == Geometry::Dot(n1, v1));

}

TEST_CASE("Normalize Vectors and Normals")
{
	Vec3f v1(1.0f, 1.0f, 1.0f);
	Normal n1(1.0f, 1.0f, 1.0f);

	Vec3f nv1 = Geometry::Normalize(v1);
}