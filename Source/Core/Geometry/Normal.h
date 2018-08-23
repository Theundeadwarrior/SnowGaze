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

		void Normalize();

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

	public:
		float x;
		float y;
		float z;
	};

	using Normal3f = Normal3<float>;
	using Normal3d = Normal3<double>;
}

#include "Core/Geometry/Normal.hpp"
