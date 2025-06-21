#include "OcclusionCulling.h"
#include "global.h"
#include "Driver.h"
#include <m_includes/XorStr/XR.hpp>
OcclusionCulling::OcclusionCulling()
{
	global::print(XR("[OcclusionCulling] Initialized"));
	uint64_t convarculling = driver::read<uint64_t>(driver::GetGameAssembly() + Class);
	global::print(XR("[OcclusionCulling] OcclusionCulling: 0x%llX"), convarculling);
	this->StaticField = driver::read<uint64_t>(convarculling + StaticField);
	global::print(XR("[OcclusionCulling] Static Fields: 0x%llX"), StaticField);
	this->Instance = driver::read<uint64_t>(StaticField + Instance);
	global::print(XR("[OcclusionCulling] Instance: 0x%llX"), Instance);
	this->DebugSettings = driver::read<uint64_t>(Instance + DebugSettings);
	global::print(XR("[OcclusionCulling] DebugSettings: 0x%llX"), Instance);
}

void OcclusionCulling::WriteLayerMask(int mask)
{
	std::cout << "layer value: " << driver::read<bool>(DebugSettings + 0x11) << std::endl;
	//driver::write(DebugSettings + 0x20, 1);
	driver::write(DebugSettings + 0x11, 0);
	global::print(XR("[OcclusionCulling] Mask Write Failure"));
}

void OcclusionCulling::WriteDebugSettings(DebugFilter debugfilter)
{
	driver::write<DebugFilter>(StaticField + 0x8C, debugfilter);
	global::print(XR("[OcclusionCulling] Debug Settings Write Failure"));
}