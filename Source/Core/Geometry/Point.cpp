#pragma once

#include "Core/Core.h"

#include "Core/Geometry/Point.h"
#include "Core/Geometry/Vector.h"

namespace SnowGaze
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

	template <typename T, typename U>
	Point3<T> operator*(U f, const Point3<T>& p)
	{
		return p * f;
	}

	template class Point3<float>;
	//template class Point3<double>;

	template Point3<float> Point3<float>::operator+(const Vector3<float>&) const;
	//template Point3d Point3d::operator+(const Vector3<float>&) const;
	//template Point3d Point3d::operator+(const Vec3d&) const;
	template Point3<float> Point3<float>::operator+(const Point3<float>& p) const;
	//template Point3d Point3d::operator+(const Point3<float>& p) const;
	//template Point3d Point3d::operator+(const Point3d& p) const;

	template Point3<float>& Point3<float>::operator+=(const Vector3<float>&);
	//template Point3d& Point3d::operator+=(const Vector3<float>&);
	//template Point3d& Point3d::operator+=(const Vec3d&);

	template Point3<float>& Point3<float>::operator+=(const Point3<float>& p);
	//template Point3d& Point3d::operator+=(const Point3<float>& p);
	//template Point3d& Point3d::operator+=(const Point3d& p);

	template Vector3<float> Point3<float>::operator-(const Point3<float>&) const;
	//template Vec3d Point3d::operator-(const Point3<float>&) const;
	//template Vec3d Point3d::operator-(const Point3d&) const;

	template Point3<float> Point3<float>::operator-(const Vector3<float>&) const;
	//template Point3d Point3d::operator-(const Vector3<float>&) const;
	//template Point3d Point3d::operator-(const Vec3d&) const;

	template Point3<float>& Point3<float>::operator-=(const Vector3<float>&);
	//template Point3d& Point3d::operator-=(const Vector3<float>&);
	//template Point3d& Point3d::operator-=(const Vec3d&);

	template Point3<float> operator*(float f, const Point3<float>& p);
}

