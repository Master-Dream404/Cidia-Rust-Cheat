#pragma once
#include "Vectors.h"

struct mono_string
{
	char buffer[128];
};

namespace unity
{
	Vector3 get_position_injected(const uintptr_t transform);
	uintptr_t get_component(uintptr_t gameObject, const char* componentNameStr);
	Vector2 CalcAngle(const Vector3& src, const Vector3& dst);
	void smooth_angle(Vector2& angles, Vector2& localViewAngles, int aimbot_smoothing);
	void normalize(Vector2& angle);
	void normalize(float& pitch, float& yaw);
};