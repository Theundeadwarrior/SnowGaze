#pragma once

namespace Core { 
	template<typename T> class Vector3; 
	template<typename T> class Point3;
}

namespace Core
{
	template<typename T>
	T Abs(T value);

	// todo lcharbonneau: rename this namespace to Vector3 ????
	namespace Vector
	{
		template<typename T>
		T Dot(const Vector3<T>& lhs, const Vector3<T>& rhs);

		template<typename T>
		T AbsDot(const Vector3<T>& lhs, const Vector3<T>& rhs);

		template<typename T>
		Vector3<T> Cross(const Vector3<T>& lhs, const Vector3<T>& rhs);

		template<typename T>
		Vector3<T> Normalize(const Vector3<T>& v);

		// v1 needs to be normalized!!
		template<typename T>
		void GetCoordinateSystem(const Vector3<T>& v1, Vector3<T>& v2, Vector3<T>& v3);
	}

	namespace Point
	{
		template <typename T>
		float Distance(const Point3<T>& p1, const Point3<T>& p2);

		template <typename T>
		float SquareDistance(const Point3<T>& p1, const Point3<T>& p2);
	}
}

#include "Core/Math/Math.hpp"
