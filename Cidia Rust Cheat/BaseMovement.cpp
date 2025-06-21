#include "BaseMovement.h"
#include "driver.h"
BaseMovement::BaseMovement(uint64_t address)
{
	this->Class = address;
}

float BaseMovement::GetGroundAngle()
{
	return driver::read<float>(Class + GroundAngle);
}

float BaseMovement::GetGroundAngleNew()
{
	return driver::read<float>(Class + GroundAngleNew);
}

float BaseMovement::GetMaxAngleClimbing()
{
	return driver::read<float>(Class + MaxAngleClimbing);
}

float BaseMovement::GetMaxAngleWalking()
{
	return driver::read<float>(Class + MaxAngleWalking);
}

float BaseMovement::GetGroundTime()
{
	return driver::read<float>(Class + GroundTime);
}

float BaseMovement::GetJumpTime()
{
	return driver::read<float>(Class + JumpTime);
}

float BaseMovement::GetLandTime()
{
	return driver::read<float>(Class + LandTime);
}

void BaseMovement::WriteGroundAngle(float angle)
{
	driver::write(Class + GroundAngle, angle);
}

void BaseMovement::WriteGroundAngleNew(float angle)
{
	driver::write(Class + GroundAngleNew, angle);
}

void BaseMovement::WriteMaxAngleClimbing(float angle)
{
	driver::write(Class + MaxAngleClimbing, angle);
}

void BaseMovement::WriteMaxAngleWalking(float angle)
{
	driver::write(Class + MaxAngleWalking, angle);

}

void BaseMovement::WriteGroundTime(float time)
{
	driver::write(Class + GroundTime, time);
}

void BaseMovement::WriteJumpTime(float time)
{
	driver::write(Class + JumpTime, time);
}

void BaseMovement::WriteLandTime(float time)
{
	driver::write(Class + LandTime, time);
}

void BaseMovement::WasFalling(bool value) {
	driver::write(Class + wasFalling, value);
}

void BaseMovement::SetPreviousVelocity(Vector3 angle) {
	driver::write(Class + previousVelocity, angle);
}