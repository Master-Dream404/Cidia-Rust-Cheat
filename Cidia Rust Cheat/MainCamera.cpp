#include "MainCamera.h"
#include "driver.h"
#include <m_includes/XorStr/XR.hpp>
#include "global.h"
MainCamera::MainCamera()
{
	global::print(XR("[MainCamera] Initialized"));

	uint64_t maincamera = driver::read<uint64_t>(driver::GetGameAssembly() + Class);// Get Class Start Address
	global::print(XR("[MainCamera] MainCamera: 0x%llX"), maincamera);
	this->StaticField = driver::read<uint64_t>(maincamera + StaticField); // Set Static Padding
	global::print(XR("[MainCamera] Static Fields: 0x%llX"), StaticField);
	this->Camera = driver::read<uint64_t>(StaticField + Camera); // Current MainCamera
	global::print(XR("[MainCamera] Camera: 0x%llX"), Camera);
	this->CameraGameObject = driver::read<uint64_t>(Camera + CameraGameObject); // get the native gameobject
	global::print(XR("[MainCamera] CameraGameObject: 0x%llX"), CameraGameObject);
}

ViewMatrix MainCamera::GetViewMatrix()
{
	ViewMatrix viewmatrix;
	viewmatrix = driver::read<ViewMatrix>(CameraGameObject + ViewMatrixOffset);
	return viewmatrix;
}

Vector3 MainCamera::GetCameraPosition() {


/*

	if (!CameraInstance)
	{
		CameraInstance = driver::read<uint64_t>(CameraGameObject + ViewMatrixOffset);
	}
	return driver::read<Vector3>(CameraInstance + 0x42C);
*/
}
