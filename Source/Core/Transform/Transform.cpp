#include "Transform.h"


namespace Core
{
	Transform::Transform(float mat[4][4])
		: m(mat)
	{
		m_Inv = GetInverse(m);
	}

	Transform::Transform(const Matrix4x4 & mat)
		: m(mat)
		, m_Inv(GetInverse(mat))
	{}

	Transform::Transform(const Matrix4x4 & mat, const Matrix4x4 & mat_inverse)
		: m(mat)
		, m_Inv(mat_inverse)
	{}

	bool Transform::IsIdentify() const
	{
		throw("Not implemented");
	}

	Transform Inverse(const Transform & t)
	{
		return Transform(t.m_Inv, t.m);
	}
}
