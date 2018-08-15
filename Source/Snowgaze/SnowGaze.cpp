#include <stdio.h>

#include "Core/Math/Math.h"
#include "Core/Math/Vector.h"

using namespace Core;

void RunTests()
{
	Vec3f v1(1.0f, 1.0f, 1.0f);

	auto v3 = v1 + v1;

}

int main()
{
	RunTests();
}