#include "Point.h"
#pragma once

namespace SnowGaze
{
	template<typename T>
	Point2<T>::Point2(T x, T y)
		: X(x)
		, Y(y)
	{
	}

	template<typename T>
	inline Point2<T> Point2<T>::operator+(const Vector2<T>& v) const
	{
		return Point2<T>(x + v.x, y + v.y);
	}

	template<typename T>
	inline Point2<T> Point2<T>::operator+(const Point2<T>& p) const
	{
		return Point2<T>(x + p.x, y + p.y);
	}

	template<typename T>
	inline Point2<T>& Point2<T>::operator+=(const Vector2<T>& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	template<typename T>
	inline Point2<T>& Point2<T>::operator+=(const Point2<T>& p)
	{
		x += p.x;
		y += p.y;
		return *this;
	}

	template<typename T>
	inline Vector2<T> Point2<T>::operator-(const Point2<T>& p) const
	{
		return Vector2<T>(x - p.x, y - p.y);
	}

	template<typename T>
	inline Point2<T> Point2<T>::operator-(const Vector2<T>& v) const
	{
		return Point2<T>(x - v.x, y - v.y);
	}

	template<typename T>
	inline Point2<T>& Point2<T>::operator-=(const Vector2<T>& v)
	{
		x -= v.x;
		y -= x.y;
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Point2<T> Point2<T>::operator*(U f) const
	{
		return Point2<T>(x * f, y * f);
	}

	template<typename T>
	template<typename U>
	inline Point2<T>& Point2<T>::operator*=(U f)
	{
		x *= f;
		y *= f;
		return *this;
	}

	template<typename T>
	template<typename U>
	inline Point2<T> Point2<T>::operator/(U f) const
	{
		return Point2<T>(x / f, y / f);
	}

	template<typename T>
	template<typename U>
	inline Point2<T>& Point2<T>::operator/=(U f)
	{
		x /= f;
		y /= f;
		return *this;
	}

	template<typename T>
	Point3<T>::Point3(T x, T y, T z)
		: x(x)
		, y(y)
		, z(z)
	{
	}

	template<typename T>
	Point3<T> Point3<T>::operator+(const Vector3<T>& v) const
	{
		return Point3(x + v.x, y + v.y, z + v.z);
	}

	template<typename T>
	Point3<T> Point3<T>::operator+(const Point3<T>& p) const
	{
		return Point3<T>(x + p.x, y + p.y, z + p.z);
	}

	template<typename T>
	Point3<T>& Point3<T>::operator+=(const Vector3<T>& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	template<typename T>
	Point3<T>& Point3<T>::operator+=(const Point3<T>& p)
	{
		x += p.x;
		y += p.y;
		z += p.z;
		return *this;
	}

	template<typename T>
	Vector3<T> Point3<T>::operator-(const Point3<T>& p) const
	{
		return Vector3<T>(x - p.x, y - p.y, z - p.z);
	}

	template<typename T>
	Point3<T> Point3<T>::operator-(const Vector3<T>& v) const
	{
		return Point3(x - v.x, y - v.y, z - v.z);
	}

	template<typename T>
	Point3<T>& Point3<T>::operator-=(const Vector3<T>& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	template<typename T>
	template<typename U>
	Point3<T> Point3<T>::operator*(U f) const
	{
		return Point3<T>(x * f, y * f, z * f);
	}

	template<typename T>
	template<typename U>
	Point3<T>& Point3<T>::operator*=(U f)
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}

	template<typename T>
	template<typename U>
	Point3<T> Point3<T>::operator/(U f) const
	{
		U inv = 1.0f / f;
		return Point3<T>(x * inv, y * inv, z * inv);
	}

	template<typename T>
	template<typename U>
	Point3<T>& Point3<T>::operator/=(U f)
	{
		U inv = 1.0f / f;
		x *= inv;
		y *= inv;
		z *= inv;
		return *this;
	}

	template<typename T, typename U>
	Point2<T> operator*(U f, const Point2<T>& p)
	{
		return p * f;
	}

	template <typename T, typename U>
	Point3<T> operator*(U f, const Point3<T>& p)
	{
		return p * f;
	}
}
