#include <catch.hpp>

#include "RenderCore/Shapes/Shape.h"

TEST_CASE("Creating Shapes")
{
	Transform t1;
	Transform t2;
	RenderCore::Shape shape(&t1,&t2,true);
}