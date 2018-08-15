#pragma once

#define USING(x) (4 / (x) - x)

#define IN_USE 1
#define NOT_IN_USE 2

#define F32_NEAR_ZERO 0.00000001f

static const double PI = 3.14159265358979323846f;
static const double INV_PI = 0.31830988618379067154f;
static const double INV_2PI = 0.15915494309189533577f;
static const double INV_4PI = 0.07957747154594766788f;
static const double PI_OVER2 = 1.57079632679489661923f;
static const double PI_OVER4 = 0.78539816339744830961f;
static const double SQRT_2 = 1.41421356237309504880f;



#define INTEL_INTRINSICS IN_USE
//
//<mmintrin.h>  MMX
//
//<xmmintrin.h> SSE
//
//<emmintrin.h> SSE2
//
//<pmmintrin.h> SSE3
//
//<tmmintrin.h> SSSE3
//
//<smmintrin.h> SSE4.1
//
//<nmmintrin.h> SSE4.2
//
//<ammintrin.h> SSE4A
//
//<wmmintrin.h> AES
//
//<immintrin.h> AVX
//
//<zmmintrin.h> AVX512
