#include "catch.hpp"

#include "Core/Geometry/Matrix.h"

TEST_CASE("Initialize Matrices")
{
	SnowGaze::Matrix4x4 m1;
	REQUIRE(m1.m[0][0] == 1);
	REQUIRE(m1.m[1][1] == 1);
	REQUIRE(m1.m[2][2] == 1);
	REQUIRE(m1.m[3][3] == 1);

	REQUIRE(m1.m[2][0] == 0);

	auto m2 = SnowGaze::GetInverse(m1);
	REQUIRE(m1 == m2);
}