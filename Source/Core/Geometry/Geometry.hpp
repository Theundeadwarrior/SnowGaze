#pragma once

#include "Core/Geometry/Vector.h"
#include "Core/Geometry/Point.h"
#include "Core/Geometry/Normal.h"
#include "Geometry.h"

namespace SnowGaze
{
	namespace Geometry
	{
		template<typename T>
		inline T Dot(const Vector3<T>& v1, const Vector3<T>& v2)
		{
			return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
		}

		template<typename T>
		inline T Dot(const Vector3<T>& lhs, const Normal3<T>& rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
		}

		template<typename T>
		inline T Dot(const Normal3<T>& lhs, const Vector3<T>& rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
		}

		template<typename T>
		inline T Dot(const Normal3<T> & lhs, const Normal3<T> & rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
		}

		template<typename T>
		inline T AbsDot(const Vector3<T>& lhs, const Vector3<T>& rhs)
		{
			return Abs(Dot(lhs, rhs));
		}

		template<typename T>
		inline T AbsDot(const Vector3<T>& lhs, const Normal3<T> & rhs)
		{
			return Abs(Dot(lhs, rhs));
		}

		template<typename T>
		inline T AbsDot(const Normal3<T> & lhs, const Vector3<T>& rhs)
		{
			return Abs(Dot(lhs, rhs));
		}

		template<typename T>
		inline T AbsDot(const Normal3<T> & lhs, const Normal3<T> & rhs)
		{
			return Abs(Dot(lhs, rhs));
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
		Normal3<T> Normalize(const Normal3<T>& n)
		{
			return n / n.GetLength();
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

		template<typename T>
		inline Normal3<T> FaceForward(const Normal3<T> & n, const Vector3<T>& v)
		{
			return (Dot(n,v) < 0.f) ? -n : n;
		}
		template<typename T>
		Normal3<T> FaceForward(const Normal3<T>& n, const Normal3<T>& n2)
		{
			return (Dot(n, n2) < 0.f) ? -n : n;
		}
	}
}
