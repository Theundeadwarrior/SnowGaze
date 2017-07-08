#pragma once

#include "Core/Geometry/Point.h"
#include "Core/Vector/Vector.h"

#include <math.h>
#include "Math.h"

namespace Core
{
	template<typename T>
	T Abs(T value)
	{
		return value > 0 ? value : -value;
	}

	namespace Vector
	{
		template<typename T>
		inline T Dot(const Vector3<T>& v1, const Vector3<T>& v2)
		{
			return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
		}

		template<typename T>
		inline T AbsDot(const Vector3<T>& v1, const Vector3<T>& v2)
		{
			return Abs(Dot(v1, v2));
		}

		template<typename T>
		inline Vector3<T> Cross(const Vector3<T>& v1, const Vector3<T>& v2)
		{
			return Vector3<T>((v1.y * v2.z) - (v1.z * v2.y),
						   (v1.z * v2.x) - (v1.x * v2.z),
						   (v1.x * v2.y) - (v1.y * v2.x));
		}
		
		template<typename T>
		inline Vector3<T> Normalize(const Vector3<T>& v)
		{
			return v / v.GetLength();
		}

		template<typename T>
		void GetCoordinateSystem(const Vector3<T>& v1, Vector3<T>& v2, Vector3<T>& v3)
		{
			if (Abs(v1.x) > Abs(v1.y))
			{
				float invLen = 1.0f / (static_cast<float>(sqrt(v1.x * v1.x + v1.z * v1.z)));
				v2 = Vector3<T>(-v1.z * invLen, 0.0f, v1.x * invLen);
			}
			else
			{
				float invLen = 1.0f / (static_cast<float>(sqrt(v1.y * v1.y + v1.z * v1.z)));
				v2 = Vector3<T>(0.0f, v1.z * invLen, -v1.y * invLen);
			}
			v3 = Cross(v1, v2);
		}
	}

	namespace Point
	{
		template<typename T>
		inline float Distance(const Point3<T>& p1, const Point3<T>& p2)
		{
			return (p1 - p2).GetLength();
		}

		template<typename T>
		inline float SquareDistance(const Point3<T>& p1, const Point3<T>& p2)
		{
			return (p1 - p2).GetSquareLength();
		}
	}
}
