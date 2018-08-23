#include "catch.hpp"

#include "Core/Geometry/Math.h"
#include "Core/Geometry/Vector.h"

#include "Core/Geometry/Vector.h"

using namespace SnowGaze;

#define VECTOR_APPROX_EQUALS(x, y) x.x == Approx(y.x) && x.y == Approx(y.y) && x.z == Approx(y.z)

TEST_CASE("Basic Vector Operations")
{
	Vector3f i(1.0f, 0.0f, 0.0f);
	Vector3f j(0.0f, 1.0f, 0.0f);
	Vector3f k(0.0f, 0.0f, 0.0f);

	// operator+
	Vector3f ij = i + j;
	REQUIRE(ij.x == Approx(i.x));
	REQUIRE(ij.y == Approx(j.y));

	Vector3f ijk = ij;
	ijk += k;
	REQUIRE(ijk.z == Approx(k.z));

	// operator-
	ijk = ijk - k;
	REQUIRE(ijk.z == Approx(0.0f));
	ijk -= j;
	REQUIRE(ijk.y == Approx(0.0f));

	// operator*
	i = i * 2.0f;
	REQUIRE(i.x == Approx(2.0f));
	i *= 0.5f;
	REQUIRE(i.x == Approx(1.0f));

	// operator/
	i /= 2;
	REQUIRE(i.x == Approx(0.5f));
}

