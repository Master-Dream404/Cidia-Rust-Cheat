#include "unity.h"
#include <Windows.h>
#include "driver.h"
#include <xmmintrin.h>
#include <emmintrin.h>
#include <algorithm>
#pragma warning( push )
#pragma warning( disable : 4556 )
#pragma warning( push )
#pragma warning( disable : 26451 )

#define M_PI       3.14159265358979323846   // pi

#define RAD2DEG(x) { (x * (180.f / M_PI)) }
#define DEG2RAD(x) { (x * (M_PI / 180.f)) }

#define RAD2DEG( x )  ( (float)(x) * (float)(180.f / M_PI) )
#define DEG2RAD( x ) ( (float)(x) * (float)(M_PI / 180.f) )


struct Vec4
{
	float x, y, z, w;
};

struct TransformAccessReadOnly
{
	ULONGLONG pTransformData;
	int index;
};

struct TransformData
{
	ULONGLONG pTransformArray;
	ULONGLONG pTransformIndices;
};

struct Matrix34
{
	Vec4 vec0;
	Vec4 vec1;
	Vec4 vec2;
};

uintptr_t unity::get_component(uintptr_t gameObject, const char* componentNameStr)
{
	if (!gameObject)
		return NULL;

	uintptr_t componentList = driver::read<uintptr_t>(gameObject + 0x30);
	for (int h = 0; h < 20; h++) // Dunno where component count is, don't care. ItemModProjectile is usually 3rd component in list.
	{
		uintptr_t component = driver::read<uintptr_t>(componentList + (0x10 * h + 0x8));
		if (!component)
			continue;

		uintptr_t unk1 = driver::read<uintptr_t>(component + 0x28);
		if (!unk1)
			continue;

		uintptr_t componentName = driver::read<uintptr_t>(unk1 + 0x0);

		std::string name = driver::read_ascii(driver::read<uintptr_t>(componentName + 0x10), 18);
		if (strcmp(name.c_str(), componentNameStr) == 0)
			return unk1;
	}

	return NULL;
}

Vector3 unity::get_position_injected(const uintptr_t pTransform)
{
	if (!pTransform)
	{

	}
	__m128 result;

	const __m128 mulVec0 = { -2.000, 2.000, -2.000, 0.000 };
	const __m128 mulVec1 = { 2.000, -2.000, -2.000, 0.000 };
	const __m128 mulVec2 = { -2.000, -2.000, 2.000, 0.000 };

	TransformAccessReadOnly pTransformAccessReadOnly = driver::read<TransformAccessReadOnly>(pTransform + 0x38);


	unsigned int index = driver::read<unsigned int>(pTransform + 0x40);
	//std::cout << "INDEX : " << index << std::endl;

	TransformData transformData = driver::read<TransformData>(pTransformAccessReadOnly.pTransformData + 0x18);
	/*
	std::cout << "pTransformArray : " << transformData.pTransformArray << std::endl;
	std::cout << "pTransformIndices : " << transformData.pTransformIndices << std::endl;
	*/

	if (transformData.pTransformArray && transformData.pTransformIndices)
	{
		result = driver::read<__m128>(transformData.pTransformArray + 0x30 * index);
		int transformIndex = driver::read<int>(transformData.pTransformIndices + 0x4 * index);

		int pSafe = 0;
		while (transformIndex >= 0 && pSafe++ < 200)
		{

			Matrix34 matrix34 = driver::read<Matrix34>(transformData.pTransformArray + 0x30 * transformIndex);

			__m128 xxxx = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0x00));	// xxxx
			__m128 yyyy = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0x55));	// yyyy
			__m128 zwxy = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0x8E));	// zwxy
			__m128 wzyw = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0xDB));	// wzyw
			__m128 zzzz = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0xAA));	// zzzz
			__m128 yxwy = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0x71));	// yxwy
			__m128 tmp7 = _mm_mul_ps(*(__m128*)(&matrix34.vec2), result);

			result = _mm_add_ps(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(
							_mm_sub_ps(
								_mm_mul_ps(_mm_mul_ps(xxxx, mulVec1), zwxy),
								_mm_mul_ps(_mm_mul_ps(yyyy, mulVec2), wzyw)),
							_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0xAA))),
						_mm_mul_ps(
							_mm_sub_ps(
								_mm_mul_ps(_mm_mul_ps(zzzz, mulVec2), wzyw),
								_mm_mul_ps(_mm_mul_ps(xxxx, mulVec0), yxwy)),
							_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0x55)))),
					_mm_add_ps(
						_mm_mul_ps(
							_mm_sub_ps(
								_mm_mul_ps(_mm_mul_ps(yyyy, mulVec0), yxwy),
								_mm_mul_ps(_mm_mul_ps(zzzz, mulVec1), zwxy)),
							_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0x00))),
						tmp7)), *(__m128*)(&matrix34.vec0));

			transformIndex = driver::read<int>(transformData.pTransformIndices + 0x4 * transformIndex);
		}
	}

	Vector3 ReturnValue;
	ReturnValue.x = result.m128_f32[0];
	ReturnValue.y = result.m128_f32[1];
	ReturnValue.z = result.m128_f32[2];

	return ReturnValue;
}

Vector2 unity::CalcAngle(const Vector3& src, const Vector3& dst)
{
	Vector3 dir = Vector3(src.x, src.y, src.z) - dst;

	const auto sqrtss = [](float in)
		{ // thx can
			__m128 reg = _mm_load_ss(&in);
			return _mm_mul_ss(reg, _mm_rsqrt_ss(reg)).m128_f32[0];
		};

	float hyp = sqrtss(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
	float nigga = roundf(dir.y);

	if (isnan(hyp))
		hyp = sqrtss(dir.x * dir.x + nigga * nigga);

	double ax = asin(dir.y / hyp);
	double ay = -atan2(dir.x, -dir.z);

	double x = RAD2DEG(ax);
	double y = RAD2DEG(ay);

	return Vector2{ static_cast<float>(x), static_cast<float>(y) };
}

void unity::normalize(float& pitch, float& yaw)
{
	if (pitch < -89.f) pitch = -89.f;
	if (pitch > 89.f) pitch = 89.f;

	while (yaw < -180.f) yaw += 360.f;
	while (yaw > 180.f) yaw -= 360.f;
}

void unity::normalize(Vector2& angle)
{
	if (angle.x < -89.f) angle.x = -89.f;
	if (angle.x > 89.f) angle.x = 89.f;

	while (angle.y < -180.f) angle.y += 360.f;
	while (angle.y > 180.f) angle.y -= 360.f;
}

#pragma warning( pop )
#pragma warning( pop )