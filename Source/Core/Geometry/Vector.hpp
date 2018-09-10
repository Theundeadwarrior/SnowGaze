#pragma once

#include "Vector.h"
#include "Core/Geometry/Normal.h"

#include <assert.h>
#include <math.h>

namespace SnowGaze
{
	template<typename T>
	inline Vector2<T>::Vector2(T x, T y)
		: x(x)
		, y(y)
	{
	}

	template<typename T>
	inline float Vector2<T>::GetLength() const
	{
		return std::sqrt(GetSquareLength());
	}

	template<typename T>
	inline float Vector2<T>::GetSquareLength() const
	{
		return x * x + y * y;
	}

	template<typename T>
	inline Vector2<T>& Vector2<T>::Normalize()
	{
		*this /= GetLength();
		return *this;
	}

	template<typename T>
	inline Vector2<T> Vector2<T>::operator+(const Vector2<T>& rhs) const
	{
		return Vector2<T>(x + rhs.x, y + rhs.y);
	}

	template<typename T>
	inline Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	template<typename T>
	inline Vector2<T> Vector2<T>::operator-(const Vector2<T>& rhs) const
	{
		return Vector2<T>(x - rhs.x, y - rhs.y);
	}

	template<typename T>
	inline Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Vector2<T> Vector2<T>::operator*(U mult) const
	{
		return Vector2<T>(x * mult, y * mult);
	}
	template<typename T>
	template<typename U>
	inline Vector2<T>& Vector2<T>::operator*=(U mult)
	{
		x *= mult;
		y *= mult;
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Vector2<T> Vector2<T>::operator/(U div) const
	{
		assert(div > F32_NEAR_ZERO || div < -F32_NEAR_ZERO);

		return Vector2<T>(x / div, y / div);
	}

	template<typename T>
	template<typename U>
	inline Vector2<T>& Vector2<T>::operator/=(U div)
	{
		assert(div > F32_NEAR_ZERO || div < -F32_NEAR_ZERO);

		x /= div;
		y /= div;
		return *this;
	}

	template<typename T>
	Vector3<T>::Vector3(T x, T y, T z)
		: x(x)
		, y(y)
		, z(z)
	{}

	template<typename T>
	inline Vector3<T>::Vector3(const Vector3& v)
		: x(v.x)
		, y(v.y)
		, z(v.z)
	{
	}

	template<typename T>
	Vector3<T>::Vector3(const Normal3<T>& n)
		: x(n.x)
		, y(n.y)
		, z(n.z)
	{
	}

	template<typename T>
	inline float Vector3<T>::GetSquareLength() const
	{
		return static_cast<float>(x * x + y * y + z * z);
	}

	template<typename T>
	inline Vector3<T>& Vector3<T>::Normalize()
	{
		*this /= GetLength();
		return *this;
	}

	template<typename T>
	inline float Vector3<T>::GetLength() const
	{
		return static_cast<float>(sqrt(GetSquareLength()));
	}

	template<typename T>
	inline Vector3<T> Vector3<T>::operator+(const Vector3<T>& rhs) const
	{
		return Vector3(x + static_cast<T>(rhs.x), y + static_cast<T>(rhs.y), z + static_cast<T>(rhs.z));
	}

	template<typename T>
	inline Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& rhs)
	{
		x += static_cast<T>(rhs.x);
		y += static_cast<T>(rhs.y);
		z += static_cast<T>(rhs.z);
		return *this;
	}

	template<typename T>
	inline Vector3<T> Vector3<T>::operator-() const
	{
		return Vector3(-x, -y, -z);
	}

	template<typename T>
	inline Vector3<T> Vector3<T>::operator-(const Vector3& rhs) const
	{
		return Vector3(x - static_cast<T>(rhs.x), y - static_cast<T>(rhs.y), z - static_cast<T>(rhs.z));
	}

	template<typename T>
	inline Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Vector3<T> Vector3<T>::operator*(U mult) const
	{
		return Vector3(x * mult, y * mult, z * mult);
	}

	template<typename T>
	template<typename U>
	inline Vector3<T>& Vector3<T>::operator*=(U mult)
	{
		x *= mult;
		y *= mult;
		z *= mult;
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Vector3<T> Vector3<T>::operator/(U div) const
	{
		assert(div > F32_NEAR_ZERO || div < -F32_NEAR_ZERO);

		float inv = 1 / div;
		return Vector3<T>(x * inv, y * inv, z * inv);
	}

	template<typename T>
	template<typename U>
	inline Vector3<T>& Vector3<T>::operator/=(U div)
	{
		assert(div > F32_NEAR_ZERO || div < -F32_NEAR_ZERO);

		U inv = 1 / div;
		x *= inv;
		y *= inv;
		z *= inv;
		return *this;
	}

	template<typename T, typename U>
	inline Vector3<T> operator*(U f, const Vector3<T>& v)
	{
		return v * f;
	}

	template<typename T, typename U>
	Vector2<T> operator*(U f, const Vector2<T>& v)
	{
		return v * f;
	}

	template<typename T>
	inline T Dot(const Vector3<T>& v1, const Vector3<T>& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	template<typename T>
	T Dot(const Vector2<T>& lhs, const Vector2<T>& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}

	template<typename T>
	inline Vector3<T> Cross(const Vector3<T>& lhs, const Vector3<T>& rhs)
	{
		double v1x = lhs.x;
		double v1y = lhs.y;
		double v1z = lhs.z;
		double v2x = rhs.x;
		double v2y = rhs.y;
		double v2z = rhs.z;

		return Vector3<T>((float)(v1y * v2z) - (float)(v1z * v2y), (float)(v1z * v2x) - (float)(v1x * v2z), (float)(v1x * v2y) - (float)(v1y * v2x));
	}
}