#include "RenderCore/Shapes/Sphere.h"

#include "Core/FloatingPoint.h"
#include "Core/Geometry/BoundingBox.h"
#include "Core/Geometry/Geometry.h"
#include "Core/Geometry/Math.h"
#include "Core/Geometry/Ray.h"
#include "Core/Geometry/Transform.h"

#include "RenderCore/Interaction/Interaction.h"

#include <algorithm>

namespace SnowGaze
{
	Sphere::Sphere(const Transform * objectToWorld, const Transform * worldToObject, bool reverseOrientation, float radius, float zMin, float zMax, float phiMax)
		: Shape(objectToWorld, worldToObject, reverseOrientation)
		, m_Radius(radius)
		, m_ZMin(Math::Clamp(std::min(zMin, zMax), -radius, radius))
		, m_ZMax(Math::Clamp(std::max(zMin, zMax), -radius, radius))
		, m_ThetaMin(std::acos(Math::Clamp(std::min(zMin, zMax) / radius, -1.0f, 1.0f)))
		, m_ThetaMax(std::acos(Math::Clamp(std::max(zMin, zMax) / radius, -1.0f, 1.0f)))
		, m_PhiMax(Radians(Math::Clamp(phiMax, 0.0f, 360.0f)))
	{
	}

	Bounds3f Sphere::GetObjectBound() const 
	{ 
		return Bounds3f(Point3f(-m_Radius, -m_Radius, m_ZMin), Point3f(m_Radius, m_Radius, m_ZMax));
	}

	void Sphere::ComputeHitPosAndPhi(Point3f& pointHit, float& phi, ErrorFloat tShapeHit, const Ray& ray) const
	{
		// Compute sphere hit position and phi
		pointHit = ray((float)tShapeHit);

		// refine sphere intersection point
		pointHit *= m_Radius / Geometry::Distance(pointHit, Point3f(0, 0, 0));

		if (pointHit.x == 0 && pointHit.y == 0)
			pointHit.x = 1e-5f * m_Radius;
		phi = std::atan2(pointHit.y, pointHit.x);
		if (phi < 0)
			phi += PI * 2;
	}

	bool Sphere::IntersectP(const Ray &ray, bool testAlphaTexture) const
	{
		float phi;
		Point3f pointHit;

		// Transform ray into object space
		Vector3f originError;
		Vector3f directionError;
		Ray objectSpaceRay = (*m_WorldToObject)(ray, originError, directionError);

		// Compute quadratic sphere coefficients
		ErrorFloat ox(ray.o.x, originError.x);
		ErrorFloat oy(ray.o.y, originError.y);
		ErrorFloat oz(ray.o.z, originError.z);

		ErrorFloat dx(ray.d.x, directionError.x);
		ErrorFloat dy(ray.d.y, directionError.y);
		ErrorFloat dz(ray.d.z, directionError.z);

		ErrorFloat a = dx * dx + dy * dy + dz * dz;
		ErrorFloat b = 2 * (dx * ox + dy * oy + dz * oz);
		ErrorFloat c = ox * ox + oy * oy + oz * oz - ErrorFloat(m_Radius) * ErrorFloat(m_Radius);

		// Solve quadratic equation for t values
		ErrorFloat t0;
		ErrorFloat t1;

		if (!Quadratic(a, b, c, &t0, &t1))
			return false;

		if (t0.UpperBound() > ray.maxt || t1.LowerBound() >= 0) // only consider coefficient within the ray
			return false;

		ErrorFloat tShapeHit = t0;
		if (tShapeHit.LowerBound() <= 0)
		{
			tShapeHit = t1;
			if (tShapeHit.UpperBound() > ray.maxt)
				return false;
		}

		ComputeHitPosAndPhi(pointHit, phi, tShapeHit, ray);

		// Test sphere intersection against clipping parameters
		if ((m_ZMin > -m_Radius && pointHit.z < m_ZMin)
			|| (m_ZMax < m_Radius && pointHit.z > m_ZMax)
			|| (phi > m_PhiMax))
		{
			if (tShapeHit == t1)
				return false;

			if (t1.UpperBound() > ray.maxt)
				return false;

			tShapeHit = t1;

			ComputeHitPosAndPhi(pointHit, phi, tShapeHit, ray);

			if ((m_ZMin > -m_Radius && pointHit.z < m_ZMin)
				|| (m_ZMax < m_Radius && pointHit.z > m_ZMax)
				|| (phi > m_PhiMax))
				return false;
		}
		return true;
	}

	bool Sphere::Intersect(const Ray& ray, float* hit, SurfaceInteraction* isect, bool testAlphaTexture) const
	{
		float phi;
		Point3f pointHit;

		// Transform ray into object space
		Vector3f originError;
		Vector3f directionError;
		Ray objectSpaceRay = (*m_WorldToObject)(ray, originError, directionError);

		// Compute quadratic sphere coefficients
		ErrorFloat ox(ray.o.x, originError.x);
		ErrorFloat oy(ray.o.y, originError.y);
		ErrorFloat oz(ray.o.z, originError.z);

		ErrorFloat dx(ray.d.x, directionError.x);
		ErrorFloat dy(ray.d.y, directionError.y);
		ErrorFloat dz(ray.d.z, directionError.z);

		ErrorFloat a = dx * dx + dy * dy + dz * dz;
		ErrorFloat b = 2 * (dx * ox + dy * oy + dz * oz);
		ErrorFloat c = ox * ox + oy * oy + oz * oz - ErrorFloat(m_Radius) * ErrorFloat(m_Radius);

		// Solve quadratic equation for t values
		ErrorFloat t0;
		ErrorFloat t1;

		if (!Quadratic(a, b, c, &t0, &t1))
			return false;

		if (t0.UpperBound() > ray.maxt || t1.LowerBound() <= 0) // only consider coefficient within the ray
			return false;

		ErrorFloat tShapeHit = t0;
		if (tShapeHit.LowerBound() <= 0)
		{
			tShapeHit = t1;
			if (tShapeHit.UpperBound() > ray.maxt)
				return false;
		}

		ComputeHitPosAndPhi(pointHit, phi, tShapeHit, ray);
			
		// Test sphere intersection against clipping parameters
		if ((m_ZMin > -m_Radius && pointHit.z < m_ZMin)
			|| (m_ZMax < m_Radius && pointHit.z > m_ZMax)
			|| (phi > m_PhiMax))
		{
			if (tShapeHit == t1)
				return false;

			if (t1.UpperBound() > ray.maxt)
				return false;

			tShapeHit = t1;

			ComputeHitPosAndPhi(pointHit, phi, tShapeHit, ray);

			if ((m_ZMin > -m_Radius && pointHit.z < m_ZMin)
				|| (m_ZMax < m_Radius && pointHit.z > m_ZMax)
				|| (phi > m_PhiMax))
				return false;
		}

		// Find parametric representation of the sphere hit
		float u = phi / m_PhiMax;
		float theta = std::acos(Math::Clamp(pointHit.z / m_Radius, -1.0f, 1.0f));
		float v = (theta - m_ThetaMin) / (m_ThetaMax - theta);

		float zRadius = std::sqrt(pointHit.x * pointHit.x + pointHit.y * pointHit.y);
		float invZRadius = 1 / zRadius;
		float cosPhi = pointHit.x * invZRadius;
		float sinPhi = pointHit.y * invZRadius;
		Vector3f dpdu(-m_PhiMax * pointHit.y, m_PhiMax * pointHit.x, 0);
		Vector3f dpdv = (m_ThetaMax - m_ThetaMin) * Vector3f(pointHit.z * cosPhi, pointHit.z * sinPhi, -m_Radius * std::sin(theta));

		// Compute sphere dn/du and dn/dv
		Vector3f d2Pduu = -m_PhiMax * m_PhiMax * Vector3f(pointHit.x, pointHit.y, 0);
		Vector3f d2Pduv = (m_ThetaMax - m_ThetaMin) * pointHit.z * m_PhiMax * Vector3f(-sinPhi, cosPhi, 0);
		Vector3f d2Pdvv = -(m_ThetaMax - m_ThetaMin) * (m_ThetaMax - m_ThetaMin) * Vector3f(pointHit.x, pointHit.y, pointHit.z);

		float E = Dot(dpdu, dpdu);
		float F = Dot(dpdu, dpdv);
		float G = Dot(dpdv, dpdv);
		Vector3f N = Cross(dpdu, dpdv).Normalize();
		float e = Dot(N, d2Pduu);
		float f = Dot(N, d2Pduv);
		float g = Dot(N, d2Pdvv);

		float invEGF2 = 1 / (E * G - F * F);
		Normal3f dndu = Normal3f((f * F - e * G) * invEGF2 * dpdu + (e * F - f * E) * invEGF2 * dpdv);
		Normal3f dndv = Normal3f((g * F - f * G) * invEGF2 * dpdu + (f * F - g * E) * invEGF2 * dpdv);

		// Compute error bounds for sphere intersection
		Vector3f pointHitError = Gamma(5) * Math::Abs(Vector3f(pointHit.x, pointHit.y, pointHit.z));

		// Initialize SurfaceInteraction from parametric information
		auto surf = SurfaceInteraction(pointHit, pointHitError, Point2f(u, v), -(ray.d), dpdu, dpdv, dndu, dndv, ray.time, this);
		*isect = (*m_ObjectToWorld)(surf);

		// Update hit for quadratic intersection
		*hit = (float)tShapeHit;

		return true;
	}

	float Sphere::GetArea() const
	{
		return m_PhiMax * m_Radius * (m_ZMax - m_ZMin);
	}

	Interaction Sphere::Sample(const Point2<float>& u, float * pdf) const
	{
		return SurfaceInteraction();
	}
}
