#include "catch.hpp"

#include "Core/Math/Math.h"
#include "Core/Geometry/Point.h"

#include <math.h>

using namespace Core;

TEST_CASE("Point Distance Operations")
{
	Point3f p1(0.0f, 0.0f, 0.0f);
	Point3f p2(1.0f, 1.0f, 1.0f);

	float distance = Point::Distance(p1, p2);
	REQUIRE(distance == sqrtf(3.0f));

	float squareDistance = Point::SquareDistance(p1, p2);
	REQUIRE(squareDistance == 3.0f);
}