#include "BaseMelee.h"
#include "Driver.h"
#include "global.h"
BaseMelee::~BaseMelee() { }

BaseMelee::BaseMelee(uint64_t helditem)
{
	this->Class = driver::read<uint64_t>(driver::GetGameAssembly() + BaseMelee_TypeInfo);
	global::print(XR("[BaseMelee] Initialized"));
	global::print(XR("[BaseMelee] Class: 0x%llX\n"), Class);
}