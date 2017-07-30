#pragma once

#include "Core/Geometry/Point.h"
#include "Core/Math/Vector.h"

namespace Core
{
	template<typename T>
	Point3<T>::Point3(T x, T y, T z)
		: x(x)
		, y(y)
		, z(z)
	{
	}

	template<typename T>
	template<typename U>
	Point3<T> Point3<T>::operator+(const Vector3<U>& v) const
	{
		return Point3(x + static_cast<T>(v.x), y + static_cast<T>(v.y), z + static_cast<T>(v.z));
	}

	template<typename T>
	template<typename U>
	Point3<T> Point3<T>::operator+(const Point3<U>& p) const
	{
		return Point3<T>(x + static_cast<T>(p.x), y + static_cast<T>(p.y), z + static_cast<T>(p.z));
	}

	template<typename T>
	template<typename U>
	Point3<T>& Point3<T>::operator+=(const Vector3<U>& v)
	{
		x += static_cast<T>(v.x);
		y += static_cast<T>(v.y);
		z += static_cast<T>(v.z);
		return *this;
	}

	template<typename T>
	template<typename U>
	Point3<T>& Point3<T>::operator+=(const Point3<U>& p)
	{
		x += static_cast<T>(p.x);
		y += static_cast<T>(p.y);
		z += static_cast<T>(p.z);
		return *this;
	}

	// Point3 - Point3 == Vector
	template<typename T>
	template<typename U>
	Vector3<T> Point3<T>::operator-(const Point3<U>& p) const
	{
		return Vector3<T>(x - static_cast<T>(p.x), y - static_cast<T>(p.y), z - static_cast<T>(p.z));
	}

	template<typename T>
	template<typename U>
	Point3<T> Point3<T>::operator-(const Vector3<U>& v) const
	{
		return Point3(x - static_cast<T>(v.x), y - static_cast<T>(v.y), z - static_cast<T>(v.z));
	}

	template<typename T>
	template<typename U>
	Point3<T>& Point3<T>::operator-=(const Vector3<U>& v)
	{
		x -= static_cast<T>(v.x);
		y -= static_cast<T>(v.y);
		z -= static_cast<T>(v.z);
		return *this;
	}

	template<typename T>
	Point3<T> Point3<T>::operator*(float f) const
	{
		return Point3<T>(x * f, y * f, z * f);
	}

	template<typename T>
	Point3<T>& Point3<T>::operator*=(float f)
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}

	template<typename T>
	Point3<T> Point3<T>::operator/(float f) const
	{
		float inv = 1.0f / f;
		return Point3<T>(x * inv, y * inv, z * inv);
	}

	template<typename T>
	Point3<T>& Point3<T>::operator/=(float f)
	{
		float inv = 1.0f / f;
		x *= inv;
		y *= inv;
		z *= inv;
		return *this;
	}

	template class Point3<float>;
	template class Point3<double>;

	template Point3f Point3f::operator+(const Vec3f&) const;
	template Point3d Point3d::operator+(const Vec3f&) const;
	template Point3d Point3d::operator+(const Vec3d&) const;
	template Point3f Point3f::operator+(const Point3f& p) const;
	template Point3d Point3d::operator+(const Point3f& p) const;
	template Point3d Point3d::operator+(const Point3d& p) const;

	template Point3f& Point3f::operator+=(const Vec3f&);
	template Point3d& Point3d::operator+=(const Vec3f&);
	template Point3d& Point3d::operator+=(const Vec3d&);

	template Point3f& Point3f::operator+=(const Point3f& p);
	template Point3d& Point3d::operator+=(const Point3f& p);
	template Point3d& Point3d::operator+=(const Point3d& p);

	template Vec3f Point3f::operator-(const Point3f&) const;
	template Vec3d Point3d::operator-(const Point3f&) const;
	template Vec3d Point3d::operator-(const Point3d&) const;

	template Point3f Point3f::operator-(const Vec3f&) const;
	template Point3d Point3d::operator-(const Vec3f&) const;
	template Point3d Point3d::operator-(const Vec3d&) const;

	template Point3f& Point3f::operator-=(const Vec3f&);
	template Point3d& Point3d::operator-=(const Vec3f&);
	template Point3d& Point3d::operator-=(const Vec3d&);
}
