#include "vectorf128.h"

namespace Core
{
	Vector4f128::Vector4f128()
		: m_Value(_mm_setzero_ps())
	{
	}

	Vector4f128::Vector4f128(float x, float y, float z, float w)
		: m_Value(_mm_setr_ps(x, y, z, w))
	{
	}

	Vector4f128::Vector4f128(float v)
		: m_Value(_mm_set_ps(v, v, v, v))
	{
	}

	Vector4f128::Vector4f128(__m128 value)
		: m_Value(value)
	{
	}

	Vector4f128::~Vector4f128()
	{
	}

	float Vector4f128::GetLength() const
	{
		return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(m_Value, m_Value, 0xff)));
	}

	float Vector4f128::GetSquareLength() const
	{
		return _mm_cvtss_f32(_mm_dp_ps(m_Value, m_Value, 0xff));
	}

	void Vector4f128::Normalize()
	{
		__m128 norm = _mm_sqrt_ps(_mm_dp_ps(m_Value, m_Value, 0xff));
		m_Value = _mm_div_ps(m_Value, norm);
	}

	Vector4f128 Vector4f128::operator+(const Vector4f128& lhs) const
	{
		return Vector4f128(_mm_add_ps(m_Value, lhs.m_Value));
	}

	Vector4f128& Vector4f128::operator+=(const Vector4f128& lhs)
	{
		m_Value = _mm_add_ps(m_Value, lhs.m_Value);
		return *this;
	}

	Vector4f128 Vector4f128::operator-(const Vector4f128& lhs) const
	{
		return Vector4f128(_mm_sub_ps(m_Value, lhs.m_Value));
	}

	Vector4f128 Vector4f128::operator-=(const Vector4f128& lhs)
	{
		m_Value = _mm_sub_ps(m_Value, lhs.m_Value);
		return *this;
	}

	Vector4f128 Vector4f128::operator*(float mult) const
	{
		return _mm_mul_ps(m_Value, Vector4f128(mult).m_Value);
	}

	Vector4f128& Vector4f128::operator*=(float mult)
	{
		m_Value = _mm_mul_ps(m_Value, Vector4f128(mult).m_Value);
		return *this;
	}

	Vector4f128 Vector4f128::operator/(float div) const
	{
		return _mm_div_ps(m_Value, Vector4f128(div).m_Value);
	}

	Vector4f128& Vector4f128::operator/=(float div)
	{
		m_Value = _mm_div_ps(m_Value, Vector4f128(div).m_Value);
		return *this;
	}

	float Vector4f128::operator[](uint32_t x) const
	{
		float values[4];
		_mm_store_ps(values, m_Value);
		return values[x];
	}

	Vector4f128 operator*(float f, const Vector4f128 & v)
	{
		return v * f;
	}
}
