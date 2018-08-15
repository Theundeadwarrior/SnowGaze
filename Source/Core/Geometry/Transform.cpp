#include "Transform.h"

#include "Core/Geometry/BoundingBox.h"
#include "Core/Geometry/Geometry.h"
#include "Core/Geometry/Normal.h"
#include "Core/Geometry/Point.h"
#include "Core/Geometry/Ray.h"
#include "Core/Geometry/Vector.h"
#include "Core/Geometry/Math.h"

#include <math.h>

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

	Point3<float> Transform::operator()(const Point3<float>& p) const
	{
		float x = p.x, y = p.y, z = p.z;
		float xp = m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z + m.m[0][3];
		float yp = m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z + m.m[1][3];
		float zp = m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z + m.m[2][3];
		float wp = m.m[3][0] * x + m.m[3][1] * y + m.m[3][2] * z + m.m[3][3];
		if (wp == 1.0f)
			return Point3<float>(xp, yp, zp);
		else
			return Point3<float>(xp, yp, zp) / wp;
	}

	Vector3<float> Transform::operator()(const Vector3<float>& v) const
	{
		float x = v.x;
		float y = v.y;
		float z = v.z;
		return Vector3<float>(m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z,
			m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z,
			m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z);
	}

	Normal Transform::operator()(const Normal & n) const
	{
		float x = n.x;
		float y = n.y;
		float z = n.z;
		return Normal(m_Inv.m[0][0] * x + m_Inv.m[1][0] * y + m_Inv.m[2][0] * z,
			m_Inv.m[0][1] * x + m_Inv.m[1][1] * y + m_Inv.m[2][1] * z,
			m_Inv.m[0][2] * x + m_Inv.m[1][2] * y + m_Inv.m[2][2] * z);
	}

	Ray Transform::operator()(const Ray & r) const
	{
		Ray ret = r;
		ret.o = operator()(ret.o);
		ret.d = operator()(ret.d);
		return ret;
	}

	RayDifferential Transform::operator()(const RayDifferential & r) const
	{
		RayDifferential ret = r;
		ret.m_HasDifferential = r.m_HasDifferential;
		ret.rxOrigin = operator()(r.rxOrigin);
		ret.ryOrigin = operator()(r.ryOrigin);
		ret.rxDirection = operator()(r.rxDirection);
		ret.ryDirection = operator()(r.ryDirection);
		return ret;
	}

	BBox Transform::operator()(const BBox & b) const
	{
		const Transform &m = *this;
		BBox result(		 m(Point3f(b.m_Min.x, b.m_Min.y, b.m_Min.z)));
		result = Union(result, m(Point3f(b.m_Max.x, b.m_Min.y, b.m_Min.z)));
		result = Union(result, m(Point3f(b.m_Min.x, b.m_Max.y, b.m_Min.z)));
		result = Union(result, m(Point3f(b.m_Min.x, b.m_Min.y, b.m_Max.z)));
		result = Union(result, m(Point3f(b.m_Min.x, b.m_Max.y, b.m_Max.z)));
		result = Union(result, m(Point3f(b.m_Max.x, b.m_Max.y, b.m_Min.z)));
		result = Union(result, m(Point3f(b.m_Max.x, b.m_Min.y, b.m_Max.z)));
		result = Union(result, m(Point3f(b.m_Max.x, b.m_Max.y, b.m_Max.z)));
		return result;
	}

	Transform Transform::operator*(const Transform & t2) const
	{
		Matrix4x4 m1 = Mul(m, t2.m);
		Matrix4x4 m2 = Mul(t2.m_Inv, m_Inv);
		return Transform(m1, m2);
	}

	bool Transform::IsIdentify() const
	{
		throw("Not implemented");
	}

	bool Transform::HasScaling() const
	{
		float la1 = (*this)(Vec3f(1, 0, 0)).GetSquareLength();
		float lb2 = (*this)(Vec3f(0, 1, 0)).GetSquareLength();
		float lc3 = (*this)(Vec3f(0, 0, 1)).GetSquareLength();

		auto notOne = [](float x) {
			return (x < 0.999f || x > 1.001f);
		};
		return notOne(la1) || notOne(lb2) || notOne(lc3);
	}

	inline bool Transform::HasSwappedHandedness() const 
	{
		float det = m.m[0][0] * (m.m[1][1] * m.m[2][2] - m.m[1][2] * m.m[2][1]) -
					m.m[0][1] * (m.m[1][0] * m.m[2][2] - m.m[1][2] * m.m[2][0]) +
					m.m[0][2] * (m.m[1][0] * m.m[2][1] - m.m[1][1] * m.m[2][0]);
		return det < 0;
	}

	Transform GetInverse(const Transform & t)
	{
		return Transform(t.m_Inv, t.m);
	}

	Transform GetTranslate(const Vector3<float>& delta)
	{
		Matrix4x4 m(1, 0, 0, delta.x,
			0, 1, 0, delta.y,
			0, 0, 1, delta.z,
			0, 0, 0, 1);

		Matrix4x4 mInv(1, 0, 0, -delta.x,
			0, 1, 0, -delta.y,
			0, 0, 1, -delta.z,
			0, 0, 0, 1);

		return Transform(m, mInv);
	}

	Transform GetScale(float x, float y, float z)
	{
		Matrix4x4 m(x, 0, 0, 0,
			0, y, 0, 0,
			0, 0, z, 0,
			0, 0, 0, 1);

		Matrix4x4 mInv(1/x, 0, 0, 0,
			0, 1/y, 0, 0,
			0, 0, 1/z, 0,
			0, 0, 0, 1);

		return Transform(m, mInv);
	}

	Transform GetRotateX(float angle)
	{
		float sinTheta = sinf(Math::Radians(angle));
		float cosTheta = cosf(Math::Radians(angle));
		Matrix4x4 m(1, 0, 0, 0,
					0, cosTheta, -sinTheta, 0,
					0, sinTheta, cosTheta, 0,
					0, 0, 0, 1);
		return Transform(m, GetTranspose(m));
	}

	Transform GetRotateY(float angle)
	{
		float sinTheta = sinf(Math::Radians(angle));
		float cosTheta = cosf(Math::Radians(angle));
		Matrix4x4 m(cosTheta, 0, sinTheta, 0,
					0, 1, 0, 0,
					-sinTheta, 0, cosTheta, 0,
					0, 0, 0, 1);
		return Transform(m, GetTranspose(m));
	}

	Transform GetRotateZ(float angle)
	{
		float sinTheta = sinf(Math::Radians(angle));
		float cosTheta = cosf(Math::Radians(angle));
		Matrix4x4 m(cosTheta, -sinTheta, 0, 0,
					sinTheta, cosTheta, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1);
		return Transform(m, GetTranspose(m));
	}
	Transform GetRotate(float angle, const Vector3<float>& axis)
	{
		Vec3f a = Geometry::Normalize(axis);
		float sinTheta = sinf(Math::Radians(angle));
		float cosTheta = cosf(Math::Radians(angle));
		Matrix4x4 m;

		// Compute rotation of first basis vector
		m.m[0][0] = a.x * a.x + (1 - a.x * a.x) * cosTheta;
		m.m[0][1] = a.x * a.y * (1 - cosTheta) - a.z * sinTheta;
		m.m[0][2] = a.x * a.z * (1 - cosTheta) + a.y * sinTheta;
		m.m[0][3] = 0;

		// Compute rotations of second and third basis vectors
		m.m[1][0] = a.x * a.y * (1 - cosTheta) + a.z * sinTheta;
		m.m[1][1] = a.y * a.y + (1 - a.y * a.y) * cosTheta;
		m.m[1][2] = a.y * a.z * (1 - cosTheta) - a.x * sinTheta;
		m.m[1][3] = 0;

		m.m[2][0] = a.x * a.z * (1 - cosTheta) - a.y * sinTheta;
		m.m[2][1] = a.y * a.z * (1 - cosTheta) + a.x * sinTheta;
		m.m[2][2] = a.z * a.z + (1 - a.z * a.z) * cosTheta;
		m.m[2][3] = 0;
		return Transform(m, GetTranspose(m));
	}

	Transform GetLookAt(const Point3<float>& pos, const Point3<float>& look, const Vector3<float>& up)
	{
		Matrix4x4 m;
		m.m[0][3] = pos.x;
		m.m[1][3] = pos.y;
		m.m[2][3] = pos.z;
		m.m[3][3] = 1.0f;

		Vec3f dir = Geometry::Normalize(look - pos);
		Vec3f left = Geometry::Normalize(Geometry::Cross(Geometry::Normalize(up), dir));
		Vec3f newUp = Geometry::Cross(dir, left);

		m.m[0][0] = left.x;
		m.m[1][0] = left.y;
		m.m[2][0] = left.z;
		m.m[3][0] = 0.0f;

		m.m[0][1] = newUp.x;
		m.m[1][1] = newUp.y;
		m.m[2][1] = newUp.z;
		m.m[3][1] = 0.0f;

		m.m[0][2] = dir.x;
		m.m[1][2] = dir.x;
		m.m[2][2] = dir.x;
		m.m[3][2] = 0.0f;

		return Transform();
	}

	AnimatedTransform::AnimatedTransform(const std::shared_ptr<Transform> & t1, float time1, const std::shared_ptr<Transform> & t2, float time2)
		: m_StartTime(time1)
		, m_EndTime(time2)
		, m_StartTransform(t1)
		, m_EndTransform(t2)
		, m_IsAnimated(t1 != t2)
	{
		DecomposeMatrix(m_StartTransform->m, m_Translation[0], m_Rotation[0], m_Scale[0]);
		DecomposeMatrix(m_EndTransform->m, m_Translation[0], m_Rotation[0], m_Scale[0]);

		m_HasRotation = Dot(m_Rotation[0], m_Rotation[1]) < 0.9995f;
	}

	void AnimatedTransform::Interpolate(float time, Transform & tranformOut) const
	{
		float dt = (time - m_StartTime) / (m_EndTime - m_StartTime);

		// early out if t < start or t > end
		if (!m_IsAnimated || time <= m_StartTime)
		{
			tranformOut = *m_StartTransform;
			return;
		}
		if (time >= m_EndTime)
		{
			tranformOut = *m_EndTransform;
			return;
		}

		// Interpolate translation
		Vec3f translation = (1.0f - dt) * m_Translation[0] + dt * m_Translation[1];

		// Interpolate rotation
		Quaternion rotation = Slerp(dt, m_Rotation[0], m_Rotation[1]);
		
		// Interpolate scale
		Matrix4x4 scale;
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				scale.m[i][j] = Math::GetLerp(dt, m_Scale[0].m[i][j], m_Scale[1].m[i][j]);
			}
		}

		tranformOut = GetTranslate(translation) * rotation.ToTransform() * Transform(scale);
	}

	Ray AnimatedTransform::operator()(const Ray &r) const {
		if (!m_IsAnimated || r.time <= m_StartTime)
		{
			return (*m_StartTransform)(r);
		}
		else if (r.time >= m_EndTime)
		{
			return (*m_EndTransform)(r);
		}
		else 
		{
			Transform t;
			Interpolate(r.time, t);
			return t(r);
		}
	}

	RayDifferential AnimatedTransform::operator()(const RayDifferential& r) const 
	{
		if (!m_IsAnimated || r.time <= m_StartTime)
			return (*m_StartTransform)(r);
		else if (r.time >= m_EndTime)
			return (*m_EndTransform)(r);
		else 
		{
			Transform t;
			Interpolate(r.time, t);
			return t(r);
		}
	}

	Point3f AnimatedTransform::operator()(float time, const Point3<float>& p) const 
	{
		if (!m_IsAnimated || time <= m_StartTime)
		{
			return (*m_StartTransform)(p);
		}
		else if (time >= m_EndTime)
		{
			return (*m_EndTransform)(p);
		}
		else
		{
			Transform t;
			Interpolate(time, t);
			return t(p);
		}
	}

	Vec3f AnimatedTransform::operator()(float time, const Vector3<float>& v) const 
	{
		if (!m_IsAnimated || time <= m_StartTime)
		{
			return (*m_StartTransform)(v);
		}
		else if (time >= m_EndTime)
		{
			return (*m_EndTransform)(v);
		}
		else
		{
			Transform t;
			Interpolate(time, t);
			return t(v);
		}
	}

	BBox AnimatedTransform::MotionBounds(const BBox & b, bool useInverse) const
	{
		if (!m_IsAnimated)
		{
			return (GetInverse(*m_StartTransform))(b);
		}

		BBox ret;
		const int nSteps = 128;
		for (int i = 0; i < nSteps; ++i)
		{
			Transform t;
			float time = Math::GetLerp(float(i) / float(nSteps - 1), m_StartTime, m_EndTime);
			Interpolate(time, t);
			if (useInverse)
			{
				t = GetInverse(t);
			}
			ret = Union(ret, t(b));
		}
		return ret;
	}

	//BBox AnimatedTransform::MotionBounds(const BBox & b) const
	//{
	//	if (!m_IsAnimated)
	//	{
	//		return (*m_StartTransform)(b);
	//	}

	//	if (m_HasRotation == false)
	//		return Union((*m_StartTransform)(b), (*m_EndTransform)(b));
	//	// Return motion bounds accounting for animated rotation
	//	BBox bounds;
	//	for (int corner = 0; corner < 8; ++corner)
	//		bounds = Union(bounds, BoundPointMotion(b.GetCorner(corner)));
	//	return bounds;
	//}

	//BBox AnimatedTransform::BoundPointMotion(const Point3f &p) const 
	//{
	//	if (!m_IsAnimated)
	//	{
	//		return BBox((*m_StartTransform)(p));
	//	}

	//	BBox bounds((*m_StartTransform)(p), (*m_EndTransform)(p));
	//	float cosTheta = Dot(m_Rotation[0], m_Rotation[1]);
	//	float theta = std::acos(Math::Clamp(cosTheta, -1, 1));
	//	for (int c = 0; c < 3; ++c) 
	//	{
	//		// Find any motion derivative zeros for the component _c_
	//		float zeros[8];
	//		int nZeros = 0;
	//		IntervalFindZeros(c1[c].Eval(p), c2[c].Eval(p), c3[c].Eval(p),
	//			c4[c].Eval(p), c5[c].Eval(p), theta, Interval(0., 1.),
	//			zeros, &nZeros);
	//		CHECK_LE(nZeros, sizeof(zeros) / sizeof(zeros[0]));

	//		// Expand bounding box for any motion derivative zeros found
	//		for (int i = 0; i < nZeros; ++i) {
	//			Point3f pz = (*this)(Lerp(zeros[i], startTime, endTime), p);
	//			bounds = Union(bounds, pz);
	//		}
	//	}
	//	return bounds;
	//}

	void DecomposeMatrix(const Matrix4x4 & m, Vector3<float>& translation, Quaternion& rotation, Matrix4x4& scale)
	{
		// Extracts translation
		translation.x = m.m[0][3];
		translation.y = m.m[1][3];
		translation.z = m.m[2][3];

		// Recompute the matrix without the translation
		Matrix4x4 matrixNoTranslation = m;
		for (uint32_t i = 0; i < 3; ++i)
		{
			matrixNoTranslation.m[i][3] = 0.0f;
			matrixNoTranslation.m[3][i] = 0.0f;
		}
		matrixNoTranslation.m[3][3] = 1.0f;

		// Extract rotation _R_ from transformation matrix
		float norm;
		int count = 0;
		Matrix4x4 rotationMatrix = matrixNoTranslation;
		do {
			// Compute next matrix _Rnext_ in series
			Matrix4x4 rotationNext;
			Matrix4x4 rotationInversedTransposed = GetInverse(GetTranspose(rotationMatrix));
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 4; ++j)
					rotationNext.m[i][j] = 0.5f * (rotationMatrix.m[i][j] + rotationInversedTransposed.m[i][j]);

			// Compute norm of difference between _R_ and _Rnext_
			norm = 0;
			for (int i = 0; i < 3; ++i) {
				float n = Math::Abs(rotationMatrix.m[i][0] - rotationNext.m[i][0]) +
					Math::Abs(rotationMatrix.m[i][1] - rotationNext.m[i][1]) +
					Math::Abs(rotationMatrix.m[i][2] - rotationNext.m[i][2]);
				norm = std::fmax(norm, n);
			}
			rotationMatrix = rotationNext;
		} while (++count < 100 && norm > .0001);

		// XXX TODO FIXME deal with flip...
		rotation = Quaternion(rotationMatrix);

		// Compute scale _S_ using rotation and original matrix
		scale = Mul(GetInverse(rotationMatrix), (matrixNoTranslation));
	}
}
