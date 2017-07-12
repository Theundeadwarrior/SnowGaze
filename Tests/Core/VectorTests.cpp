#include "catch.hpp"

#include "Core/Math/Math.h"
#include "Core/Math/Vector.h"

using namespace Core;

#define VECTOR_APPROX_EQUALS(x, y) x.x == Approx(y.x) && x.y == Approx(y.y) && x.z == Approx(y.z)

TEST_CASE("Basic Vector Operations")
{
	Vec3f i(1.0f, 0.0f, 0.0f);
	Vec3f j(0.0f, 1.0f, 0.0f);
	Vec3f k(0.0f, 0.0f, 0.0f);

	// operator+
	Vec3f ij = i + j;
	REQUIRE(ij.x == Approx(i.x));
	REQUIRE(ij.y == Approx(j.y));

	Vec3f ijk = ij;
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