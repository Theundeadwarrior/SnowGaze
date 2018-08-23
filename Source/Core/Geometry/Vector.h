#pragma once

#include "Core/Core.h"

namespace SnowGaze { template<typename T> class Normal3; }

namespace SnowGaze
{
	template<typename T>
	class Vector2
	{
	public:
		Vector2() = default;
		Vector2(T x, T y);
		~Vector2() = default;

		float GetLength() const;
		float GetSquareLength() const;

		void Normalize();
		
		Vector2<T> operator+(const Vector2<T>& rhs) const;
		Vector2<T>& operator+=(const Vector2<T>& rhs);

		Vector2<T> operator-(const Vector2<T>& rhs) const;
		Vector2<T>& operator-=(const Vector2<T>& rhs);

		template<typename U>
		Vector2<T> operator*(U mult) const;

		template<typename U>
		Vector2<T>& operator*=(U mult);

		template<typename U>
		Vector2<T> operator/(U div) const;

		template<typename U>
		Vector2<T>& operator/=(U div);

	public:
		T x;
		T y;
	};


	template<typename T>
	class Vector3
	{
	public:
		Vector3() = default;
		Vector3(T x, T y, T z);
		Vector3(const Vector3<T>& v);
		explicit Vector3(const Normal3<T>& n);
		~Vector3() = default;

		float GetLength() const;
		float GetSquareLength() const;

		void Normalize();

		Vector3<T> operator+(const Vector3<T>& rhs) const;
	
		Vector3<T>& operator+=(const Vector3<T>& rhs);

		Vector3<T> operator-(const Vector3<T>& rhs) const;

		Vector3<T>& operator-=(const Vector3<T>& rhs);

		template<typename U>
		Vector3<T> operator*(U mult) const;

		template<typename U>
		Vector3<T>& operator*=(U mult);

		template<typename U>
		Vector3<T> operator/(U div) const;

		template<typename U>
		Vector3<T>& operator/=(U div);

	public:
		T x;
		T y;
		T z;
	};

	template<typename T, typename U>
	Vector3<T> operator*(U f, const Vector3<T>& v);

	template<typename T, typename U>
	Vector2<T> operator*(U f, const Vector2<T>& v);

	template<typename T>
	T Dot(const Vector3<T>& lhs, const Vector3<T>& rhs);

	template<typename T>
	T Dot(const Vector2<T>& lhs, const Vector2<T>& rhs);

	using Vector2f = Vector2<float>;
	using Vector2d = Vector2<double>;
	using Vector3f = Vector3<float>;
	using Vector3d = Vector3<double>;
}

#include "Core/Geometry/Vector.hpp"
