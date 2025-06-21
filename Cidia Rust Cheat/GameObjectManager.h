#pragma once
#include <string>
#include "Vectors.h"
class GameObjectManager
{
private:
	uint64_t GameObjectManagerOffset = 0x1D0B490;
public:
	Vector3 GetCameraPosition();
};