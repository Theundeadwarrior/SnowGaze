#pragma once

namespace Core { template<typename T> class Vector3; }

namespace Core
{
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
		Point3<T>& operator+=(const Vector3<U>& v);

		template<typename U>
		Vector3<T> operator-(const Point3<U>& p) const;

		template<typename U>
		Point3<T> operator-(const Vector3<U>& v) const;

		template<typename U>
		Point3<T>& operator-=(const Vector3<U>& v);
		

	public:
		T x;
		T y;
		T z;
	};

	typedef Point3<float> Point3f;
	typedef Point3<double> Point3d;
}
