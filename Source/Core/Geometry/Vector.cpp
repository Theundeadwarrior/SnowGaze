#pragma once

#include "Core/Core.h"
#include "Core/Geometry/Vector.h"
#include "Core/Geometry/Normal.h"

#include <assert.h>
#include <math.h>

namespace Core
{
	template<typename T>
	Vector3<T>::Vector3(T x, T y, T z)
		: x(x)
		, y(y)
		, z(z)
	{}

	template<typename T>
	Vector3<T>::Vector3(const Normal& n)
		: x(n.x)
		, y(n.y)
		, z(n.z)
	{
	}

	template<typename T>
	float Vector3<T>::GetSquareLength() const
	{
		return static_cast<float>(x * x + y * y + z * z);
	}

	template<typename T>
	void Vector3<T>::Normalize()
	{
		*this /= GetLength();
	}

	template<typename T>
	float Vector3<T>::GetLength() const
	{
		return static_cast<float>(sqrt(GetSquareLength()));
	}

	template<typename T>
	template<typename U>
	Vector3<T> Vector3<T>::operator+(const Vector3<U>& rhs) const
	{
		return Vector3(x + static_cast<T>(rhs.x), y + static_cast<T>(rhs.y), z + static_cast<T>(rhs.z));
	}

	template<typename T>
	template<typename U>
	Vector3<T>& Vector3<T>::operator+=(const Vector3<U>& rhs)
	{
		x += static_cast<T>(rhs.x);
		y += static_cast<T>(rhs.y);
		z += static_cast<T>(rhs.z);
		return *this;
	}

	template<typename T>
	template<typename U>
	Vector3<T> Vector3<T>::operator-(const Vector3<U>& rhs) const
	{
		return Vector3(x - static_cast<T>(rhs.x), y - static_cast<T>(rhs.y), z - static_cast<T>(rhs.z));
	}

	template<typename T>
	template<typename U>
	Vector3<T>& Vector3<T>::operator-=(const Vector3<U>& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	template<typename T>
	Vector3<T> Vector3<T>::operator*(float mult) const
	{
		return Vector3(x * mult, y * mult, z * mult);
	}

	template<typename T>
	Vector3<T>& Vector3<T>::operator*=(float mult)
	{
		x *= mult;
		y *= mult;
		z *= mult;
		return *this;
	}

	template<typename T>
	Vector3<T> Vector3<T>::operator/(float div) const
	{
		assert(div > F32_NEAR_ZERO || div < -F32_NEAR_ZERO);

		float inv = 1 / div;
		return Vector3<T>(x * inv, y * inv, z * inv);
	}

	template<typename T>
	Vector3<T>& Vector3<T>::operator/=(float div)
	{
		assert(div > F32_NEAR_ZERO || div < -F32_NEAR_ZERO);

		float inv = 1 / div;
		x *= inv;
		y *= inv;
		z *= inv;
		return *this;
	}

	template<typename T>
	Vector3<T> operator*(float f, const Vector3<T>& v)
	{
		return v * f;
	}

	template<typename T>
	T Dot(const Vector3<T>& v1, const Vector3<T>& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	// todo lcharbonneau: define the rest of the template explicit instantiations

	template class Vector3<float>;
	template class Vector3<double>;


	template Vector3<float> operator*(float f, const Vector3<float>& rhs);
//	template Vec3d operator*(float f, const Vec3d& rhs);

	template Vector3<float> Vector3<float>::operator+(const Vector3<float>& rhs) const;
	//template Vec3d Vec3d::operator+(const Vector3<float>& rhs) const;
	//template Vec3d Vec3d::operator+(const Vec3d& rhs) const;
	template Vector3<float>& Vector3<float>::operator+=(const Vector3<float>& rhs);
	//template Vec3d& Vec3d::operator+=(const Vector3<float>& rhs);
	//template Vec3d& Vec3d::operator+=(const Vec3d& rhs);

	template Vector3<float> Vector3<float>::operator-(const Vector3<float>& rhs) const;
	//template Vec3d Vec3d::operator-(const Vector3<float>& rhs) const;
	//template Vec3d Vec3d::operator-(const Vec3d& rhs) const;
	template Vector3<float>& Vector3<float>::operator-=(const Vector3<float>& rhs);
	//template Vec3d& Vec3d::operator-=(const Vector3<float>& rhs);
	//template Vec3d& Vec3d::operator-=(const Vec3d& rhs);
}