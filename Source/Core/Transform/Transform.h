#pragma once

#include "Core/Math/Matrix.h"

namespace Core
{
	class Transform
	{
	public:
		Transform() = default;
		Transform(float mat[4][4]);
		Transform(const Matrix4x4& mat);
		Transform(const Matrix4x4& mat, const Matrix4x4& mat_inverse);
		~Transform() = default;

		friend Transform Inverse(const Transform& t);

		bool IsIdentify() const;

	private:
		Matrix4x4 m;
		Matrix4x4 m_Inv;
	};
}
