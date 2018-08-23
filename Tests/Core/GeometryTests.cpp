#include "catch.hpp"

#include "Core/Geometry/Geometry.h"
#include "Core/Geometry/Vector.h"

using namespace SnowGaze;

TEST_CASE("Dot Product")
{
	Vector3f v1(1.0f, 0.0f, 0.0f);
	Normal3f n1(1.0f, 0.0f, 0.0f);

	REQUIRE(Geometry::Dot(v1, n1) == Geometry::Dot(n1, v1));

}

TEST_CASE("Normalize Vectors and Normals")
{
	Vector3f v1(1.0f, 1.0f, 1.0f);
	Normal3f n1(1.0f, 1.0f, 1.0f);

	Vector3f nv1 = Geometry::Normalize(v1);
}