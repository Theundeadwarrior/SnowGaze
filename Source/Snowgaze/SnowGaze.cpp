#include <stdio.h>

#include "Core/Math/Math.h"
#include "Core/Vector/Vector.h"

using namespace Core;

void RunTests()
{
	{
		Vec3f v1(1.0f, 1.0f, 1.0f);
		Vec3f v2(2.0f, 0.0f, 1.0f);

		auto v3 = v1 + v2;
		assert(v3.x == v1.x + v2.x && v3.y == v1.y + v2.y && v3.z == v1.z + v2.z);

		v3 += v1;
		assert(v3.x == 4.0f && v3.y == 2.0f && v3.z == 3.0f);
		
		v3 /= 0.5;
		v3 *= 0.5;
	}

	{
		Vec3f v1(1.0f, 1.0f, 1.0f);
		Vec3f v2(2.0f, 0.0f, 1.0f);
		Vec3f v3;

		auto dot = Vector::Dot(v1, v2);
		auto absDot = Vector::AbsDot(v1, v2);
		auto cross = Vector::Cross(v1, v2);
		auto normalized = Vector::Normalize(v1);
		v1.Normalize();

		Vector::GetCoordinateSystem(v1, v2, v3);
		auto dot12 = Vector::Dot(v1, v2);
		auto dot13 = Vector::Dot(v1, v3);
		auto dot23 = Vector::Dot(v2, v3);
	}
}

int main()
{
	RunTests();
}