#include "FloatingPoint.h"

#include "Core/Core.h"

#include <assert.h>
#include <algorithm>
#include <limits>

namespace SnowGaze
{
	ErrorFloat::ErrorFloat(float value, float error)
		: m_Value(value)
	{
		if (error == 0.0f)
		{
			m_Low = m_Value;
			m_High = m_Value;
		}
		else
		{
			m_Low = NextFloatDown(value - error);
			m_High = NextFloatUp(value + error);
		}
	}

	ErrorFloat ErrorFloat::operator+(ErrorFloat lhs) const
	{
		ErrorFloat r;
		r.m_Value = m_Value + lhs.m_Value;

		r.m_Low = NextFloatDown(m_Low + lhs.m_Low);
		r.m_High = NextFloatUp(m_High + lhs.m_High);

		return r;
	}

	ErrorFloat ErrorFloat::operator-(ErrorFloat lhs) const
	{
		ErrorFloat r;
		r.m_Value = m_Value - lhs.m_Value;

		r.m_Low = NextFloatDown(m_Low - lhs.m_Low);
		r.m_High = NextFloatUp(m_High - lhs.m_High);

		return r;
	}

	ErrorFloat ErrorFloat::operator*(ErrorFloat lhs) const
	{
		ErrorFloat r;

		r.m_Value = m_Value * lhs.m_Value;

		float prod[4] = {
			LowerBound() * lhs.LowerBound(), UpperBound() * lhs.LowerBound(),
			LowerBound() * lhs.UpperBound(), UpperBound() * lhs.UpperBound() };
		r.m_Low = NextFloatDown(
			std::min(std::min(prod[0], prod[1]), std::min(prod[2], prod[3])));
		r.m_High = NextFloatUp(
			std::max(std::max(prod[0], prod[1]), std::max(prod[2], prod[3])));
		r.Check();
		return r;
	}

	ErrorFloat ErrorFloat::operator/(ErrorFloat lhs) const
	{
		ErrorFloat r;
		r.m_Value = m_Value / lhs.m_Value;
		if (lhs.m_Low < 0 && lhs.m_High > 0) 
		{
			// Bah. The interval we're dividing by straddles zero, so just
			// return an interval of everything.
			r.m_Low = -std::numeric_limits<float>::infinity();
			r.m_High = std::numeric_limits<float>::infinity();
		}
		else 
		{
			float div[4] = {LowerBound() / lhs.LowerBound(), UpperBound() / lhs.LowerBound(), LowerBound() / lhs.UpperBound(), UpperBound() / lhs.UpperBound() };
			r.m_Low = NextFloatDown(std::min(std::min(div[0], div[1]), std::min(div[2], div[3])));
			r.m_High = NextFloatUp(std::max(std::max(div[0], div[1]), std::max(div[2], div[3])));
		}
		r.Check();
		return r;
	}

	bool ErrorFloat::operator==(ErrorFloat lhs) const
	{
		return m_Value == lhs.m_Value;
	}

	void ErrorFloat::Check() const
	{
		if (!std::isinf(m_Low) && !std::isnan(m_Low) 
		&& !std::isinf(m_High) && !std::isnan(m_High))
			assert(m_Low < m_High);
	}

	ErrorFloat operator+(float add, ErrorFloat lhs)
	{
		return ErrorFloat(add) + ErrorFloat(lhs);
	}

	ErrorFloat operator*(float mult, ErrorFloat lhs)
	{
		return ErrorFloat(mult) * lhs;
	}

	bool Quadratic(ErrorFloat A, ErrorFloat B, ErrorFloat C, ErrorFloat *t0, ErrorFloat *t1) 
	{
		// Find quadratic discriminant
		double discrim = (double)B.m_Value * (double)B.m_Value  - 4. * (double)A.m_Value * (double)C.m_Value;
		if (discrim < 0.) return false;
		double rootDiscrim = std::sqrt(discrim);

		ErrorFloat floatRootDiscrim((float)rootDiscrim, (float)(MachineEpsilon * rootDiscrim));

		// Compute quadratic _t_ values
		ErrorFloat q;
		if ((float)B < 0)
			q = -.5 * (B - floatRootDiscrim);
		else
			q = -.5 * (B + floatRootDiscrim);
		*t0 = q / A;
		*t1 = C / q;
		if ((float)*t0 >(float)*t1) std::swap(*t0, *t1);
		return true;
	}
}
