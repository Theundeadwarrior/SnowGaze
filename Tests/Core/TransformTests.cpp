#include "catch.hpp"
#include "Core/Geometry/Point.h"
#include "Core/Geometry/Ray.h"
#include "Core/Geometry/Transform.h"

using namespace SnowGaze;
TEST_CASE("Transform on rays uses move.")
{
	Point3f origin(0.0f, 0.0f, 0.0f);
	Vector3f dir(1.0f, 1.0f, 1.0f);
	Ray ray(origin, dir, 0.0f);

	Transform t = GetTranslate(Vector3f(2.0f, 2.0f, 2.0f));
	ray = t(ray);
}