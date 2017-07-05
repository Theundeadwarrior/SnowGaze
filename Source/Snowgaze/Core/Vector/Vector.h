#pragma once
#include <stdint.h>

namespace Core
{
	template<typename T>
	class Vector3
	{
		typedef T value_type;

	public:
		Vector3() {};
		Vector3(T x, T y, T z);
		~Vector3();

		float GetLength() const;
		float GetSquareLength() const;

		void Normalize();

		template <typename U>
		Vector3<T> operator+(const Vector3<U>& rhs) const;
	
		template <typename U>
		Vector3<T>& operator+=(const Vector3<U>& rhs);

		template <typename U>
		Vector3<T> operator-(const Vector3<U>& rhs) const;

		template <typename U>
		Vector3<T>& operator-=(const Vector3<U>& rhs);

		Vector3<T> operator*(float mult) const;
		Vector3<T>& operator*=(float mult);

		Vector3<T> operator/(float div) const;
		Vector3<T>& operator/=(float div);

	public:
		T x;
		T y;
		T z;
	};

	typedef Vector3<float> Vec3f;
	typedef Vector3<double> Vec3d;
}

#include "Core/Vector/Vector.hpp"
