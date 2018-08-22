#pragma once

#include "Core/Core.h"

namespace SnowGaze { class Normal; }

namespace SnowGaze
{
	template<typename T>
	class Vector3
	{
	public:
		Vector3() = default;
		Vector3(T x, T y, T z);
		explicit Vector3(const Normal& n);
		~Vector3() = default;

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

	template<typename T>
	Vector3<T> operator*(float f, const Vector3<T>& v);

	template<typename T>
	T Dot(const Vector3<T>& lhs, const Vector3<T>& rhs);

	using Vec3f = Vector3<float>;
}


