#include "Normal.h"

#include "Core/Core.h"
#include "Core/Vector/Vector.h"

#include <assert.h>
#include <math.h>


namespace Core
{
	template<typename T>
	inline Normal::Normal(const Vector3<T>& v)
		: x(static_cast<float>(v.x))
		, y(static_cast<float>(v.y))
		, z(static_cast<float>(v.z))
	{
	}

	Normal::Normal(float x, float y, float z)
		: x(x)
		, y(y)
		, z(z)
	{}

	float Normal::GetLength() const
	{
		return sqrtf(GetSquareLength());

	}

	float Normal::GetSquareLength() const
	{
		return x * x + y * y + z * z;
	}

	void Normal::Normalize()
	{
		*this /= GetLength();
	}

	Normal Normal::operator+(const Normal & rhs) const
	{
		return Normal(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	Normal& Normal::operator+=(const Normal & rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	Normal Normal::operator-(const Normal & rhs) const
	{
		return Normal(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	Normal & Normal::operator-=(const Normal & rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	Normal Normal::operator*(float mul) const
	{
		return Normal(x * mul, y * mul, z * mul);
	}

	Normal & Normal::operator*=(float mul)
	{
		x *= mul;
		y *= mul;
		z *= mul;
		return *this;
	}

	Normal Normal::operator/(float div) const
	{
		assert(div > F32_NEAR_ZERO || div < -F32_NEAR_ZERO);

		float inv = 1.0f / div;
		return Normal(x * inv, y * inv, z * inv);
	}

	Normal& Normal::operator/=(float div)
	{
		assert(div > F32_NEAR_ZERO || div < -F32_NEAR_ZERO);

		float inv = 1 / div;
		x *= inv;
		y *= inv;
		z *= inv;
		return *this;
	}

	template Normal::Normal(const Vec3f&);
	template Normal::Normal(const Vec3d&);
}
