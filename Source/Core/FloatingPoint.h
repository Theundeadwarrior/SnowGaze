#pragma once

#include "Core/Core.h"

namespace SnowGaze
{
	class ErrorFloat
	{
	public:
		ErrorFloat() = default;
		ErrorFloat(float value, float error = 0.0f);

		ErrorFloat operator+(ErrorFloat lhs) const;
		ErrorFloat operator-(ErrorFloat lhs) const;
		ErrorFloat operator*(ErrorFloat lhs) const;
		ErrorFloat operator/(ErrorFloat lhs) const;

		bool operator==(ErrorFloat lhs) const;

		explicit operator float() const { return m_Value; }
		explicit operator double() const { return m_Value; }

		float LowerBound() const { return m_Low; }
		float UpperBound() const { return m_High; }

	private:
		void Check() const;

		float m_Value;
		float m_Low;
		float m_High;

		friend float;
		friend bool Quadratic(ErrorFloat A, ErrorFloat B, ErrorFloat C, ErrorFloat *t0, ErrorFloat *t1);
	};

	ErrorFloat operator+(float add, ErrorFloat lhs);
	ErrorFloat operator*(float mult, ErrorFloat lhs);
	bool Quadratic(ErrorFloat A, ErrorFloat B, ErrorFloat C, ErrorFloat *t0, ErrorFloat *t1);
}
