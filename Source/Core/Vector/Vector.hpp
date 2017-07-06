#pragma once

#include "Core/Core.h"

#include <assert.h>
#include <math.h>
#include "Vector.h"

namespace Core
{
	template<typename T>
	inline Vector3<T>::Vector3(T x, T y, T z)
		: x(x)
		, y(y)
		, z(z)
	{}

	template<typename T>
	inline Vector3<T>::~Vector3()
	{}

	template<typename T>
	inline float Vector3<T>::GetSquareLength() const 
	{ 
		return x * x + y * y + z * z; 
	}

	template<typename T>
	inline void Vector3<T>::Normalize()
	{
		*this /= GetLength();
	}

	template<typename T>
	inline float Vector3<T>::GetLength() const 
	{ 
		return static_cast<float>(sqrt(GetSquareLength()));
	}

	template<typename T>
	template<typename U>
	inline Vector3<T> Vector3<T>::operator+(const Vector3<U>& rhs) const
	{
		return Vector3(x + static_cast<T>(rhs.x), y + static_cast<T>(rhs.y), z + static_cast<T>(rhs.z));
	}

	template<typename T>
	template<typename U>
	inline Vector3<T>& Vector3<T>::operator+=(const Vector3<U>& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Vector3<T> Vector3<T>::operator-(const Vector3<U>& rhs) const
	{
		return Vector3(x - static_cast<T>(rhs.x), y - static_cast<T>(rhs.y), z - static_cast<T>(rhs.z));
	}

	template<typename T>
	template<typename U>
	inline Vector3<T>& Vector3<T>::operator-=(const Vector3<U>& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	template<typename T>
	inline Vector3<T> Vector3<T>::operator*(float mult) const
	{
		return Vector3(x * mult, y * mult, z * mult);
	}

	template<typename T>
	inline Vector3<T>& Vector3<T>::operator*=(float mult)
	{
		x *= mult;
		y *= mult;
		z *= mult;
		return *this;
	}
	template<typename T>
	inline Vector3<T> Vector3<T>::operator/(float div) const
	{
		assert(div > F32_NEAR_ZERO || div < -F32_NEAR_ZERO);

		float inv = 1 / div;
		return Vector3<T>(x * inv, y * inv, z * inv);
	}
	template<typename T>
	inline Vector3<T>& Vector3<T>::operator/=(float div)
	{
		assert(div > F32_NEAR_ZERO || div < -F32_NEAR_ZERO);

		float inv = 1 / div;
		x *= inv;
		y *= inv;
		z *= inv;
		return *this;
	}
}