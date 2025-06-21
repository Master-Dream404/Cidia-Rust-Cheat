#include "BaseNetworkable.h"
#include "driver.h"
#include <m_includes/XorStr/XR.hpp>
#include "global.h"
BaseNetworkable::BaseNetworkable()
{
	uint64_t networkable = driver::read<uint64_t>(driver::GetGameAssembly() + Class); // Get Class Start Address
	global::print(XR("[BaseNetworkable] BaseNetworkable: 0x%llX"), networkable);
	this->StaticField = driver::read<uint64_t>(networkable + StaticField); // Set Static Padding
	global::print(XR("[BaseNetworkable] Static Fields: 0x%llX"), StaticField);


	this->ClientEntities = driver::read<uint64_t>(StaticField + ClientEntities);
	global::print(XR("[BaseNetworkable] ClientEntities: 0x%llX"), ClientEntities);


	this->EntityList = driver::read<uint64_t>(ClientEntities + EntityList); // entity realm
	global::print(XR("[BaseNetworkable] EntityList: 0x%llX"), EntityList);

	this->BufferList = driver::read<uint64_t>(EntityList + 0x28);
	global::print(XR("[BaseNetworkable] BufferList: 0x%llX"), BufferList);// ListDictionary<TKey, TVal> : IEnumerable<KeyValuePair<TKey, TVal>>, IEnumerable

	this->ObjectList = driver::read<uint64_t>(BufferList + 0x18);
	global::print(XR("[BaseNetworkable] ObjectList: 0x%llX"), ObjectList);

	this->ObjectListSize = driver::read<uint32_t>(BufferList + 0x10);
	global::print(XR("[BaseNetworkable] ObjectListSize: 0x%lX"), ObjectListSize);
}
void BaseNetworkable::ItterateEntities()
{
	for (int i = 0; i < ObjectListSize; i++)
	{
		uint64_t currentobject = driver::read<uint64_t>(ObjectList + (0x20 + (i * 8)));
		if (!currentobject)
			continue;

		uint64_t baseobject = driver::read<uint64_t>(currentobject + 0x10);
		if (!baseobject)
			continue;

		uint64_t object = driver::read<uint64_t>(baseobject + 0x30);

		if (!object)
			continue;

		uint64_t prefab = driver::read<uint64_t>(object + 0x60);
		if (!prefab)
			continue;

		WORD tag = driver::read<WORD>(object + 0x54);
		if (tag == 0)
			continue;

		std::cout << "[BaseNetworkable] Tag: " << tag << std::endl;
	}

}

unsigned int BaseNetworkable::GetObjectSize() {
	return this->ObjectListSize;
}
uintptr_t BaseNetworkable::GetObjectList() {
	return this->ObjectList;
}
uintptr_t BaseNetworkable::GetElement(int index) {
	return driver::read<uintptr_t>(ObjectList + (0x20 + (index * 8)));
}

std::string BaseNetworkable::GetElementClassName(uintptr_t element) {
	uintptr_t object = driver::read<uintptr_t>(element);
	if (!object)
		return {};

	uintptr_t pName = driver::read<uintptr_t>(object + 0x10);
	if (!pName)
	{
		global::print(XR("No pName"));
		return {};
	}

	std::string nice = driver::read_unicode(pName, 32);

	return nice;

}

Vector3 BaseNetworkable::GetObjectPosition(uintptr_t object) {
	uintptr_t visual = driver::read<uintptr_t>(object + 0x08);
	uintptr_t object_state = driver::read<uintptr_t>(visual + 0x38);

	if (!object_state)
	{
		global::print(XR("No object state!"));
		return { -1, -1, -1 };
	}

	return driver::read<Vector3>(object_state + 0x90);
}

uintptr_t BaseNetworkable::GetObjectComponent(uintptr_t object) {
	uintptr_t visual = driver::read<uintptr_t>(object + 0x08);
	uintptr_t object_state = driver::read<uintptr_t>(visual + 0x38);
	return object_state;
}

std::string BaseNetworkable::GetClassNameE(uintptr_t object) {
	uintptr_t object_v1 = driver::read<uintptr_t>(object);
	if (!object_v1)
		return {};

	uintptr_t pName = driver::read<uintptr_t>(object_v1 + 0x10);
	if (!pName)
		return {};

	std::string nice = driver::read_ascii(pName, 32);

	return nice;
}