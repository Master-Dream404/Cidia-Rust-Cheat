
#include "TODSky.h"
#include "driver.h"
#include <m_includes/XorStr/XR.hpp>
#include "global.h"
TODSky::TODSky()
{
	global::print(XR("[TODSky] Initialized"));
	Class = driver::read<uint64_t>(driver::GetGameAssembly() + Class);
	global::print(XR("[TODSky] Class: 0x%llX"), Class);
	StaticField = driver::read<uint64_t>(Class + StaticField); // static field and 0x0 is 	private static List<TOD_Sky> instances;
	StaticField = driver::read<uint64_t>(StaticField + 0x0);
	uint64_t intancevalues = driver::read<uint64_t>(StaticField + 0x10); // 0x10 = list values
	Instance = driver::read<uint64_t>(intancevalues + 0x20); // first value in instances list
	global::print(XR("[TODSky] Instance: 0x%llX"), Instance);
	NightParameters = driver::read<uint64_t>(Instance + NightParameters);
	DayParameters = driver::read<uint64_t>(Instance + DayParameters);

}
void TODSky::WriteNightLightIntensity(float value)
{
	//global::print(XR("WriteNightLightIntensity %f", value));
	driver::write(NightParameters + LightIntensityNight, value);
}
void TODSky::WriteNightAmbientMultiplier(float value)
{
	//global::print(XR("WriteNightAmbientMultiplier %f", value));
	driver::write(NightParameters + AmbientMultiplierNight, value);
}
void TODSky::WriteDayAmbientMultiplier(float value)
{
	//global::print(XR("WriteDayAmbientMultiplier %f", value));
	driver::write(DayParameters + AmbientMultiplierDay, value);
}

float TODSky::GetNightLightIntensity() {
	return driver::read<float>(NightParameters + LightIntensityNight);
}
float TODSky::GetNightAmbientMultiplier() {
	return driver::read<float>(NightParameters + AmbientMultiplierNight);
}
float TODSky::GetDayAmbientMultiplier() {
	return driver::read<float>(DayParameters + AmbientMultiplierDay);
}

//uint64_t ReflectionParameters = 0xA0;//	public TOD_ReflectionParameters -> Reflection;
//uint64_t CullingMask = 0x18;// TOD_ReflectionParameters : public LayerMask CullingMask;
void TODSky::WriteCullingMaskLayers(int mask) {
	uintptr_t Reflection = driver::read<uintptr_t>(Class + ReflectionParameters);
	if (!Reflection)
		global::print(XR("failed to find mask"));

	driver::write(Reflection + 0x18, mask);
	global::print(XR("Reflection set to %i "), mask);
}