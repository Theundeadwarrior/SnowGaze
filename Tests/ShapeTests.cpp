#include <catch.hpp>

#include "Core/Geometry/Transform.h"
#include "Core/Geometry/Ray.h"
#include "RenderCore/Interaction/Interaction.h"
#include "RenderCore/Shapes/Shape.h"
#include "RenderCore/Shapes/Sphere.h"

#include "Core/Geometry/Point.h"
#include "Core/Geometry/Vector.h"

using namespace SnowGaze;

TEST_CASE("Creating Shapes")
{
	SnowGaze::Transform t1;
	SnowGaze::Transform t2;
	SnowGaze::Sphere sphere(&t1, &t2, false, 2.0f, -2.0f, 2.0f, 360.0f);
	SnowGaze::Ray ray(Point3f(-5,0,0), Vector3f(1.0f,0.0f,0.0f));
	float hitValue;
	SurfaceInteraction surf;
	sphere.Intersect(ray, &hitValue, &surf, false);
}