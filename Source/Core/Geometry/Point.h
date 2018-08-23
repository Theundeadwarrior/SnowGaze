#pragma once

namespace SnowGaze { 
	template<typename T> class Vector3;
	template<typename T> class Vector2;
}

namespace SnowGaze
{
	template<typename T>
	class Point2
	{
	public:
		Point2() = default;
		Point2(T x, T y);
		~Point2() = default;

		Point2<T> operator+(const Vector2<T>& v) const;
		Point2<T> operator+(const Point2<T>& p) const;
		Point2<T>& operator+=(const Vector2<T>& v);
		Point2<T>& operator+=(const Point2<T>& p);

		Vector2<T> operator-(const Point2<T>& p) const;
		Point2<T> operator-(const Vector2<T>& v) const;
		Point2<T>& operator-=(const Vector2<T>& v);

		template<typename U>
		Point2<T> operator*(U f) const;

		template<typename U>
		Point2<T>& operator*=(U f);

		template<typename U>
		Point2<T> operator/(U f) const;

		template<typename U>
		Point2<T>& operator/=(U f);

	private:
		T x;
		T y;
	};

	template<typename T>
	class Point3
	{
	public:
		Point3() = default;
		Point3(T x, T y, T z);
		~Point3() = default;

		Point3<T> operator+(const Vector3<T>& v) const;
		Point3<T> operator+(const Point3<T>& p) const;
		Point3<T>& operator+=(const Vector3<T>& v);
		Point3<T>& operator+=(const Point3<T>& p);

		Vector3<T> operator-(const Point3<T>& p) const;
		Point3<T> operator-(const Vector3<T>& v) const;
		Point3<T>& operator-=(const Vector3<T>& v);

		template<typename U>
		Point3<T> operator*(U f) const;
		
		template<typename U>
		Point3<T>& operator*=(U f);

		template<typename U>
		Point3<T> operator/(U f) const;

		template<typename U>
		Point3<T>& operator/=(U f);

	public:
		T x;
		T y;
		T z;
	};

	template <typename T, typename U>
	inline Point2<T> operator*(U f, const Point2<T>& p);

	template <typename T, typename U>
	inline Point3<T> operator*(U f, const Point3<T>& p);

	using Point2f = Point2<float>;
	using Point2d = Point2<double>;
	using Point3f = Point3<float>;
	using Point3d = Point3<double>;
}

#include "Core/Geometry/Point.hpp"
