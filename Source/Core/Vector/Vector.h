#pragma once

namespace Core
{
	template<typename T>
	class Vector3
	{
	public:
		Vector3() = default;
		Vector3(T x, T y, T z);
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

	typedef Vector3<float> Vec3f;
	typedef Vector3<double> Vec3d;
}


