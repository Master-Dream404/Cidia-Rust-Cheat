#pragma once
#include <cstdint>
#include "Vectors.h"
class BaseMovement
{
	uint64_t Class = 0x0;
	uint64_t GroundAngle = 0xCC; // private float groundAngle;
	uint64_t GroundAngleNew = 0xD0; //private float groundAngleNew;
	uint64_t MaxAngleClimbing = 0x98; //public float maxAngleClimbing;
	uint64_t MaxAngleWalking = 0x94; //public float maxAngleWalking;
	uint64_t GroundTime = 0xD4; // 	private float groundTime;
	uint64_t JumpTime = 0xD8; //private float jumpTime;
	uint64_t LandTime = 0xDC; //private float landTime;
	uint64_t wasFalling = 0x150;
	uint64_t previousVelocity = 0xEC;
public:
	BaseMovement(uint64_t address);
	float GetGroundAngle();
	float GetGroundAngleNew();
	float GetMaxAngleClimbing();
	float GetMaxAngleWalking();
	float GetGroundTime();
	float GetJumpTime();
	float GetLandTime();
	// Create a scatter handle and then execute it after the function calls.
	void WriteGroundAngle(float angle);
	void WriteGroundAngleNew(float angle);
	void WriteMaxAngleClimbing(float angle);
	void WriteMaxAngleWalking(float angle);
	void WriteGroundTime(float time);
	void WriteJumpTime(float time);
	void WriteLandTime(float time);
	void WasFalling(bool value);
	void SetPreviousVelocity(Vector3 angle);
};