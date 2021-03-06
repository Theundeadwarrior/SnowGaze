#pragma once

#include "Core/Core.h"
#include "Core/Geometry/Vector.h"

#include <assert.h>
#include <math.h>


namespace SnowGaze
{
	template<typename T>
	inline Normal3<T>::Normal3(const Vector3<T>& v)
		: x(static_cast<float>(v.x))
		, y(static_cast<float>(v.y))
		, z(static_cast<float>(v.z))
	{
	}

	template<typename T>
	Normal3<T>::Normal3()
		: x(1)
		, y(1)
		, z(1)
	{
	}

	template<typename T>
	Normal3<T>::Normal3(float x, float y, float z)
		: x(x)
		, y(y)
		, z(z)
	{}

	template<typename T>
	float Normal3<T>::GetLength() const
	{
		return sqrtf(GetSquareLength());
	}

	template<typename T>
	float Normal3<T>::GetSquareLength() const
	{
		return x * x + y * y + z * z;
	}

	template<typename T>
	Normal3<T>& Normal3<T>::Normalize()
	{
		*this /= GetLength();
		return *this;
	}

	template<typename T>
	Normal3<T> Normal3<T>::operator+(const Normal3 & rhs) const
	{
		return Normal3<T>(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	template<typename T>
	Normal3<T>& Normal3<T>::operator+=(const Normal3 & rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	template<typename T>
	Normal3<T> Normal3<T>::operator-(const Normal3 & rhs) const
	{
		return Normal3(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	template<typename T>
	Normal3<T> & Normal3<T>::operator-=(const Normal3 & rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	template<typename T>
	template<typename U>
	Normal3<T> Normal3<T>::operator*(U mul) const
	{
		return Normal3<T>(x * mul, y * mul, z * mul);
	}

	template<typename T>
	template<typename U>
	Normal3<T> & Normal3<T>::operator*=(U mul)
	{
		x *= mul;
		y *= mul;
		z *= mul;
		return *this;
	}

	template<typename T>
	template<typename U>
	Normal3<T> Normal3<T>::operator/(U div) const
	{
		assert(div > F32_NEAR_ZERO || div < -F32_NEAR_ZERO);

		float inv = 1.0f / div;
		return Normal3(x * inv, y * inv, z * inv);
	}

	template<typename T>
	template<typename U>
	Normal3<T>& Normal3<T>::operator/=(U div)
	{
		assert(div > F32_NEAR_ZERO || div < -F32_NEAR_ZERO);

		float inv = 1 / div;
		x *= inv;
		y *= inv;
		z *= inv;
		return *this;
	}

	template<typename T>
	inline Normal3<T> Normal3<T>::operator-() const
	{
		return *this * -1;
	}

	template<typename T>
	bool Normal3<T>::operator==(const Normal3<T>& rhs) const
	{
		return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
	}

	template<typename T>
	bool Normal3<T>::operator!=(const Normal3<T>& rhs) const
	{
		return (x != rhs.x) || (y != rhs.y) || (z != rhs.z);
	}

	template<typename T>
	Normal3<T> GetFaceForward(const Normal3<T>& n, const Normal3<T>& n2)
	{
		return (Geometry::Dot(n, n2) < 0.f) ? -n : n;
	}
}
