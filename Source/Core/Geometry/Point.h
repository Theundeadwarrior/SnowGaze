#pragma once

namespace SnowGaze { template<typename T> class Vector3; }

namespace SnowGaze
{
	template<typename T>
	class Point2
	{
	public:
		Point2() = default;
		Point2(T x, T y);
		~Point2() = default;

	private:
		T X;
		T Y;
	};

	template<typename T>
	class Point3
	{
	public:
		Point3() = default;
		Point3(T x, T y, T z);
		~Point3() = default;

		template<typename U>
		Point3<T> operator+(const Vector3<U>& v) const;
		
		template<typename U>
		Point3<T> operator+(const Point3<U>& p) const;

		template<typename U>
		Point3<T>& operator+=(const Vector3<U>& v);

		template<typename U>
		Point3<T>& operator+=(const Point3<U>& p);

		template<typename U>
		Vector3<T> operator-(const Point3<U>& p) const;

		template<typename U>
		Point3<T> operator-(const Vector3<U>& v) const;

		template<typename U>
		Point3<T>& operator-=(const Vector3<U>& v);

		Point3<T> operator*(float f) const;
		Point3<T>& operator*=(float f);

		Point3<T> operator/(float f) const;
		Point3<T>& operator/=(float f);

	public:
		T x;
		T y;
		T z;
	};

	template <typename T, typename U>
	inline Point3<T> operator*(U f, const Point3<T>& p);

	using Point3f = Point3<float>;
	template<typename T>
	Point2<T>::Point2(T x, T y)
		: X(x)
		, Y(y)
	{
	}
}
