
#pragma once
#include <string>
class TODSky // class TOD_Sky
{
	/*
	    {
      "Address": 63116264,
      "Name": "TOD_Sky_TypeInfo",
      "Signature": "TOD_Sky_c*"
    },
	*/
	uint64_t Class = 0x3C3BBA8;
	uint64_t StaticField = 0xB8;
	uint64_t NightParameters = 0x60; // public TOD_NightParameters Night;
	uint64_t DayParameters = 0x58; // 	public TOD_DayParameters Day;
	uint64_t Instance = 0;
	uint64_t AmbientMultiplierDay = 0x50; // TOD_NightParameters -> public float AmbientMultiplier;
	uint64_t AmbientMultiplierNight = 0x50; // TOD_NightParameters -> public float AmbientMultiplier;
	uint64_t LightIntensityDay = 0x48; // TOD_NightParameters -> public float LightIntensity;
	uint64_t LightIntensityNight = 0x48; // TOD_NightParameters -> public float LightIntensity;


	uint64_t ReflectionParameters = 0xA0;//	public TOD_ReflectionParameters -> Reflection; tod sky
public:
	TODSky();
	void WriteNightLightIntensity(float value);
	void WriteNightAmbientMultiplier(float value);
	void WriteDayAmbientMultiplier(float value);
	float GetNightLightIntensity();
	float GetNightAmbientMultiplier();
	float GetDayAmbientMultiplier();
	void WriteCullingMaskLayers(int mask);
};

