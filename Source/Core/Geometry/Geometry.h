#pragma once

namespace Core {
	template<typename T> class Vector3;
	template<typename T> class Point3;
	class Normal;
}

namespace Core
{
	namespace Geometry
	{
		// Dot & AbsDot
		template<typename T>
		T Dot(const Vector3<T>& lhs, const Vector3<T>& rhs);

		template<typename T>
		T Dot(const Vector3<T>& lhs, const Normal& rhs);

		template<typename T>
		T Dot(const Normal& lhs, const Vector3<T>& rhs);

		template<typename T>
		T Dot(const Normal& lhs, const Normal& rhs);

		template<typename T>
		T AbsDot(const Vector3<T>& lhs, const Vector3<T>& rhs);

		template<typename T>
		T AbsDot(const Vector3<T>& lhs, const Normal& rhs);

		template<typename T>
		T AbsDot(const Normal& lhs, const Vector3<T>& rhs);

		template<typename T>
		T AbsDot(const Normal& lhs, const Normal& rhs);

		template<typename T>
		Vector3<T> Cross(const Vector3<T>& lhs, const Vector3<T>& rhs);

		template<typename T>
		Vector3<T> Normalize(const Vector3<T>& v);

		Normal Normalize(const Normal& n);

		// v1 needs to be normalized!!
		template<typename T>
		void GetCoordinateSystem(const Vector3<T>& v1, Vector3<T>& v2, Vector3<T>& v3);

		template <typename T>
		float Distance(const Point3<T>& p1, const Point3<T>& p2);

		template <typename T>
		float SquareDistance(const Point3<T>& p1, const Point3<T>& p2);

		// Might need to implement for other combinations.
		template<typename T>
		Normal FaceForward(const Normal& n, const Vector3<T>& v);
	}
}

#include "Core/Geometry/Geometry.hpp"
