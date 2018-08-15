#include "Core/Geometry/Point/pointf128.h"

#include "Core/Geometry/Vector/vectorf128.h"

namespace Core
{
	Point4f128::Point4f128(float x, float y, float z, float w)
		: m_Value(_mm_setr_ps(x, y, z, w))
	{
	}

	Point4f128 Point4f128::operator+(const Vector4f128 & v) const
	{
		return Point4f128(_mm_add_ps(m_Value, v.GetValue()));
	}

	Point4f128 Point4f128::operator+(const Point4f128 & p) const
	{
		return Point4f128(_mm_add_ps(m_Value, p.m_Value));
	}

	Point4f128& Point4f128::operator+=(const Vector4f128 & v)
	{
		m_Value = _mm_add_ps(m_Value, v.GetValue());
		return *this;
	}

	Point4f128 & Point4f128::operator+=(const Point4f128 & p)
	{
		m_Value = _mm_add_ps(m_Value, p.m_Value);
		return *this;
	}

	Vector4f128 Point4f128::operator-(const Point4f128 & p)
	{
		return Vector4f128(_mm_sub_ps(m_Value, p.m_Value));
	}

	Point4f128 Point4f128::operator-(const Vector4f128 & v) const
	{
		return Point4f128(_mm_sub_ps(m_Value, v.GetValue()));
	}

	Point4f128& Point4f128::operator-=(const Vector4f128 & v)
	{
		m_Value = _mm_sub_ps(m_Value, v.GetValue());
		return *this;
	}

	Point4f128 Point4f128::operator*(float mult) const
	{
		return Point4f128(_mm_mul_ps(m_Value, _mm_set_ps(mult,mult,mult,mult)));
	}

	Point4f128 & Point4f128::operator*=(float mult)
	{
		m_Value = _mm_mul_ps(m_Value, _mm_set_ps(mult, mult, mult, mult));
		return *this;
	}

	Point4f128 Point4f128::operator/(float div) const
	{
		return Point4f128(_mm_div_ps(m_Value, _mm_set_ps(div, div, div, div)));
	}

	Point4f128 & Point4f128::operator/=(float div)
	{
		m_Value = _mm_div_ps(m_Value, _mm_set_ps(div, div, div, div));
		return *this;
	}

	float Point4f128::operator[](uint32_t x) const
	{
		float values[4];
		_mm_store_ps(values, m_Value);
		return values[x];
	}


	Point4f128::Point4f128(__m128 value)
		: m_Value(value)
	{
	}
}
