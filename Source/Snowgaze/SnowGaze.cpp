#include <stdio.h>

#include "Core/Geometry/Math.h"
#include "Core/Geometry/Vector.h"

using namespace SnowGaze;

void RunTests()
{
	Vector3f v1(1.0f, 1.0f, 1.0f);

	auto v3 = v1 + v1;

}

int main()
{
	RunTests();
}