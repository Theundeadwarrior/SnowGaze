#pragma once

namespace Core { template<typename T> class Vector3; }

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
}

#include "Core/Math/Math.hpp"
