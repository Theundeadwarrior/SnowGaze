#pragma once

//todo: add Normal2 and change Normal to Normal3. Also change mult and div functions to use template U instead of float.

namespace SnowGaze { template<typename T> class Vector3; }

namespace SnowGaze
{
	template<typename T>
	class Normal3
	{
	public:
		Normal3();
		explicit Normal3(const Vector3<T>& v);
		Normal3(float x, float y, float z);
		Normal3(const Normal3<T>&) = default;
		~Normal3() = default;

		float GetLength() const;
		float GetSquareLength() const;

		Normal3<T>& Normalize();

		Normal3<T> operator+(const Normal3<T>& rhs) const;
		Normal3<T>& operator+=(const Normal3<T>& rhs);

		Normal3<T> operator-(const Normal3<T>& rhs) const;
		Normal3<T>& operator-=(const Normal3<T>& rhs);

		template<typename U>
		Normal3<T> operator*(U mul) const;
		
		template<typename U>
		Normal3<T>& operator*=(U mul);

		template<typename U>
		Normal3<T> operator/(U div) const;

		template<typename U>
		Normal3<T>& operator/=(U div);

		Normal3<T> operator-() const;

		bool operator==(const Normal3<T>& rhs) const;
		bool operator!=(const Normal3<T>& rhs) const;

	public:
		float x;
		float y;
		float z;
	};

	template<typename T>
	Normal3<T> GetFaceForward(const Normal3<T>& n, const Normal3<T>& n2);

	using Normal3f = Normal3<float>;
	using Normal3i = Normal3<int>;
}

#include "Core/Geometry/Normal.hpp"
