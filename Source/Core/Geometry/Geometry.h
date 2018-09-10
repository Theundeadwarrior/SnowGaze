#pragma once

namespace SnowGaze {
	template<typename T> class Vector3;
	template<typename T> class Point3;
	template<typename T> class Normal3;
}

namespace SnowGaze
{
	namespace Geometry
	{
		// Dot & AbsDot
		//template<typename T>
		//T Dot(const Vector3<T>& lhs, const Vector3<T>& rhs);

		template<typename T>
		T Dot(const Vector3<T>& lhs, const Normal3<T>& rhs);

		template<typename T>
		T Dot(const Normal3<T>& lhs, const Vector3<T>& rhs);

		template<typename T>
		T Dot(const Normal3<T>& lhs, const Normal3<T>& rhs);

		template<typename T>
		T AbsDot(const Vector3<T>& lhs, const Vector3<T>& rhs);

		template<typename T>
		T AbsDot(const Vector3<T>& lhs, const Normal3<T>& rhs);

		template<typename T>
		T AbsDot(const Normal3<T>& lhs, const Vector3<T>& rhs);

		template<typename T>
		T AbsDot(const Normal3<T>& lhs, const Normal3<T>& rhs);

		template<typename T>
		Vector3<T> Cross(const Vector3<T>& lhs, const Vector3<T>& rhs);

		template<typename T>
		Vector3<T> Normalize(const Vector3<T>& v);

		template<typename T>
		inline Normal3<T> Normalize(const Normal3<T>& n);

		// v1 needs to be normalized!!
		template<typename T>
		void GetCoordinateSystem(const Vector3<T>& v1, Vector3<T>& v2, Vector3<T>& v3);

		template <typename T>
		float Distance(const Point3<T>& p1, const Point3<T>& p2);

		template <typename T>
		float SquareDistance(const Point3<T>& p1, const Point3<T>& p2);

		// Might need to implement for other combinations.
		template<typename T>
		Normal3<T> FaceForward(const Normal3<T>& n, const Vector3<T>& v);

		template<typename T>
		Normal3<T> FaceForward(const Normal3<T>& n, const Normal3<T>& n2);
	}
}

#include "Core/Geometry/Geometry.hpp"
