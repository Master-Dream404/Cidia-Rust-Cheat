#include "ConvarAdmin.h"
#include "global.h"
#include <m_includes/XorStr/XR.hpp>
#include "Driver.h"
ConvarAdmin::ConvarAdmin()
{
	global::print(XR("[ConvarAdmin] Initialized"));
	uint64_t graphics = driver::read<uint64_t>(driver::GetGameAssembly() + Class);
	global::print(XR("[ConvarAdmin] ConvarAdmin: 0x%llX", graphics));
	this->StaticField = driver::read<uint64_t>(graphics + StaticField); // Set Static Padding
	global::print(XR("[ConvarAdmin] Static Fields: 0x%llX", StaticField));
}

void ConvarAdmin::ClearVisionInWater(bool value)
{
	driver::write(StaticField + AdminUnderWaterEffect, value);
	global::print(XR("[ConvarAdmin] Failed to write AdminUnderWaterEffect"));
}
void ConvarAdmin::SetAdminTime(float value)
{
	if (value == 0)
		value = -1;// this is just easier to manage with a slider

	driver::write(StaticField + AdminTime, value);
	global::print(XR("[ConvarAdmin] Failed to write AdminTime"));

}
