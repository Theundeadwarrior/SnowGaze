#pragma once

namespace SnowGaze
{
	template<typename T> class Bounds3;
	class Ray;
	class SurfaceInteraction;

	class Primitive
	{
	public:
		virtual Bounds3<float> WorldBound() const = 0;
		virtual bool Intersect(const Ray &r, SurfaceInteraction *) const = 0;
		virtual bool IntersectP(const Ray &r) const = 0;

		//virtual const AreaLight *GetAreaLight() const = 0;		//virtual const Material *GetMaterial() const = 0;		//virtual void ComputeScatteringFunctions(SurfaceInteraction *isect, MemoryArena &arena, TransportMode mode, bool allowMultipleLobes) const = 0;

		const Primitive *primitive = nullptr;
		//BSDF *bsdf = nullptr;
		//BSSRDF *bssrdf = nullptr;
	};
}

