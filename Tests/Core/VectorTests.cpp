#include "catch.hpp"

#include "Core/Geometry/Math.h"
#include "Core/Geometry/Vector.h"

#include "Core/Geometry/Vector/vectorf128.h"

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

TEST_CASE("Vector 4f using __m128")
{
	Vector4f128 v4f1(0.0f, 1.0f, 2.0f, 0.0f);
	Vector4f128 v4f2(1.0f, 0.0f, -1.0f, 0.0f);

	REQUIRE(v4f2[0] == Approx(1.0f));


}