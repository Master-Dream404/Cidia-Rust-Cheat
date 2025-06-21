#include "GameObjectManager.h"
#include "Driver.h"

/*
uint64_t GameObjectManager::GetGameObjectManager() {
	return driver::read<uintptr_t>(driver::GetGameAssembly() + GameObjectManagerOffset);
}

*/

Vector3 GameObjectManager::GetCameraPosition() {
	uintptr_t GameObjectManager = driver::read<uintptr_t>(driver::GetUnityPlayer() + GameObjectManagerOffset);
	if (!GameObjectManager)
		return {};

	uintptr_t tagged_objects = driver::read<uintptr_t>(GameObjectManager + 0x8);
	if (!tagged_objects)
		return {};

	uintptr_t game_object = driver::read<uintptr_t>(tagged_objects + 0x10);
	if (!game_object)
		return {};

	uintptr_t object_class = driver::read<uintptr_t>(game_object + 0x30);
	if (!object_class)
		return {};

	uintptr_t camera_instance = driver::read<uintptr_t>(object_class + 0x18);

	return driver::read<Vector3>(camera_instance + 0x42C);

}