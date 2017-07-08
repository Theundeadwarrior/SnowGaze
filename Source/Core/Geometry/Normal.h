#pragma once

namespace Core { template<typename T> class Vector3; }

namespace Core
{
	class Normal
	{
	public:
		template<typename T>
		explicit Normal(const Vector3<T>& v);

		Normal(float x, float y, float z);
		Normal(const Normal&) = default;
		~Normal() = default;

		float GetLength() const;
		float GetSquareLength() const;

		void Normalize();

		Normal operator+(const Normal& rhs) const;
		Normal& operator+=(const Normal& rhs);

		Normal operator-(const Normal& rhs) const;
		Normal& operator-=(const Normal& rhs);

		Normal operator*(float mul) const;
		Normal& operator*=(float mul);

		Normal operator/(float div) const;
		Normal& operator/=(float div);

	public:
		float x;
		float y;
		float z;
	};
}
