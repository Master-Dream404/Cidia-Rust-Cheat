#include "ConvarGraphics.h"
#include "driver.h"
#include <m_includes/XorStr/XR.hpp>
#include "global.h"
ConvarGraphics::ConvarGraphics()
{
	global::print(XR("[ConvarGraphics] Initialized"));
	uint64_t graphics = driver::read<uint64_t>(driver::GetGameAssembly() + Class); // Get Class Start Address
	global::print(XR("[ConvarGraphics] ConvarGraphics: 0x%llX"), graphics);
	this->StaticField = driver::read<uint64_t>(graphics + StaticField); // Set Static Padding
	global::print(XR("[ConvarGraphics] Static Fields: 0x%llX"), StaticField);
	std::cout << driver::read<float>(StaticField + 0x18) << std::endl;
	std::cout << driver::read<float>(StaticField + 0x1C) << std::endl;
	std::cout << driver::read<float>(StaticField + 0x28) << std::endl;
	std::cout << driver::read<float>(StaticField + 0x2C) << std::endl;
	std::cout << driver::read<float>(StaticField + 0x50) << std::endl;
	std::cout << driver::read<float>(StaticField + 0x64) << std::endl;
	std::cout << driver::read<float>(StaticField + 0x68) << std::endl;
	std::cout << driver::read<float>(StaticField + 0x74) << std::endl;
	std::cout << driver::read<float>(StaticField + 0x7C) << std::endl;
	std::cout << driver::read<float>(StaticField + 0x98) << std::endl;
	std::cout << driver::read<float>(StaticField + 0x9C) << std::endl;
}
void ConvarGraphics::WriteFOV(float fov)
{
	driver::write(StaticField + FOV, fov);
}

float ConvarGraphics::GetFov() {
	return driver::read<float>(StaticField + FOV);
}