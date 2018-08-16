#include "Core/Geometry/Quaternion/quaternionf128.h"

#include "Core/Geometry/Math.h"
#include "Core/Geometry/Transform.h"

namespace Core
{
	Quaternion4f128::Quaternion4f128()
		: m_Value(_mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f))
	{
	}

	Quaternion4f128::Quaternion4f128(const Transform & t)
	{
		const Matrix4x4 &m = t.GetMatrix();
		float v[4];
		float trace = m.m[0][0] + m.m[1][1] + m.m[2][2];
		if (trace > 0.f) {
			// Compute v[3] from matrix trace, then xyz
			// 4w^2 = m[0][0] + m[1][1] + m[2][2] + m[3][3] (but m[3][3] == 1)
			float s = sqrtf(trace + 1.0f);

			v[3] = s / 2.0f;
			s = 0.5f / s;
			v[0] = (m.m[2][1] - m.m[1][2]) * s;
			v[1] = (m.m[0][2] - m.m[2][0]) * s;
			v[2] = (m.m[1][0] - m.m[0][1]) * s;
		}
		else {
			// Compute largest of $x$, $y$, or $z$, then remaining components
			const int nxt[3] = { 1, 2, 0 };
			float q[3];
			int i = 0;
			if (m.m[1][1] > m.m[0][0]) i = 1;
			if (m.m[2][2] > m.m[i][i]) i = 2;
			int j = nxt[i];
			int k = nxt[j];
			float s = sqrtf((m.m[i][i] - (m.m[j][j] + m.m[k][k])) + 1.0f);
			q[i] = s * 0.5f;
			if (s != 0.f) s = 0.5f / s;
			v[3] = (m.m[k][j] - m.m[j][k]) * s;
			q[j] = (m.m[j][i] + m.m[i][j]) * s;
			q[k] = (m.m[k][i] + m.m[i][k]) * s;
			v[0] = q[0];
			v[1] = q[1];
			v[2] = q[2];
		}
		m_Value = _mm_setr_ps(v[1], v[2], v[3], v[4]);
	}

	Quaternion4f128 Quaternion4f128::operator+(const Quaternion4f128 & rhs) const
	{
		return Quaternion4f128(_mm_add_ps(m_Value, rhs.m_Value));
	}

	Quaternion4f128 & Quaternion4f128::operator+=(const Quaternion4f128 & rhs)
	{
		m_Value = _mm_add_ps(m_Value, rhs.m_Value);
		return *this;
	}

	Quaternion4f128 Quaternion4f128::operator-(const Quaternion4f128 & rhs) const
	{
		return Quaternion4f128(_mm_sub_ps(m_Value, rhs.m_Value));
	}

	Quaternion4f128 & Quaternion4f128::operator-=(const Quaternion4f128 & rhs)
	{
		m_Value = _mm_sub_ps(m_Value, rhs.m_Value);
		return *this;
	}

	Quaternion4f128 Quaternion4f128::operator*(float f) const
	{
		return Quaternion4f128(_mm_mul_ps(m_Value, _mm_set_ps(f, f, f, f)));
	}

	Quaternion4f128 & Quaternion4f128::operator*=(float f)
	{
		m_Value = _mm_mul_ps(m_Value, _mm_set_ps(f, f, f, f));
		return *this;
	}

	Quaternion4f128 Quaternion4f128::operator/(float f) const
	{
		return Quaternion4f128(_mm_div_ps(m_Value, _mm_set_ps(f, f, f, f)));
	}

	Quaternion4f128 & Quaternion4f128::operator/=(float f)
	{
		m_Value = _mm_div_ps(m_Value, _mm_set_ps(f, f, f, f));
		return *this;
	}

	Transform Quaternion4f128::ToTransform() const
	{
		float v[4];
		_mm_store_ps(v, m_Value);

		float xx = v[0] * v[0], yy = v[1] * v[1], zz = v[2] * v[2];
		float xy = v[0] * v[1], xz = v[0] * v[2], yz = v[1] * v[2];
		float wx = v[0] * v[3], wy = v[1] * v[3], wz = v[2] * v[3];

		Matrix4x4 m;
		m.m[0][0] = 1 - 2 * (yy + zz);
		m.m[0][1] = 2 * (xy + wz);
		m.m[0][2] = 2 * (xz - wy);
		m.m[1][0] = 2 * (xy - wz);
		m.m[1][1] = 1 - 2 * (xx + zz);
		m.m[1][2] = 2 * (yz + wx);
		m.m[2][0] = 2 * (xz + wy);
		m.m[2][1] = 2 * (yz - wx);
		m.m[2][2] = 1 - 2 * (xx + yy);

		// Transpose since we are left-handed.  Ugh.
		return Transform(GetTranspose(m), m);
	}

	Quaternion4f128::Quaternion4f128(__m128 value)
	{
		m_Value = value;
	}

	Quaternion4f128 operator*(float f, const Quaternion4f128 & v)
	{
		return v * f;
	}

	float Dot(const Quaternion4f128 & q1, const Quaternion4f128 & q2)
	{
		return _mm_cvtss_f32(_mm_dp_ps(q1.GetValue(), q2.GetValue(), 0xff));
	}

	Quaternion4f128 Normalize(const Quaternion4f128 & q)
	{
		__m128 dotResult = _mm_dp_ps(q.GetValue(), q.GetValue(), 0xff);
		return Quaternion4f128(_mm_mul_ps(q.GetValue(), _mm_rsqrt_ps(dotResult)));
	}

	Quaternion4f128 Slerp(float t, const Quaternion4f128 & q1, const Quaternion4f128 & q2)
	{
		float cosTheta = Dot(q1, q2);
		if (cosTheta > 0.9995f)
		{
			return Normalize((1.0f - t) * q1 + t * q2);
		}
		else
		{
			float theta = acosf(Math::Clamp(cosTheta, -1.0f, 1.0f));
			float thetap = theta * t;
			Quaternion4f128 qperp = Normalize(q2 - q2 * cosTheta);
			return q1 * cosf(thetap) + qperp * sinf(thetap);
		}
	}
}
