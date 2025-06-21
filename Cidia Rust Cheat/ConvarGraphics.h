#pragma once
#include <cstdint>
class ConvarGraphics //Convar.Graphics
{
	/*
	Script.json
	  "Name": "ConVar.Graphics_TypeInfo", -> b3fd18a2de1d993a3d23ff9fc6cd3b17f65e5d10_TypeInfo
	  "Signature": "ConVar_Graphics_c*"

	*/
	uint64_t Class = 0x3C795F0;
	//Dump.cs / DummyDLL
	uint64_t StaticField = 0xB8;// Static Padding To Access Static Fields
	uint64_t FOV = 0x2C;// private static float _fov;

	/*
		// Token: 0x0400698E RID: 27022
	[Token(Token = "0x400698E")]
	[FieldOffset(Offset = "0x2C")]
	private static float %167222b8c4cedf7f4e3a22013e455ceffc740da6;

		// Token: 0x0400698B RID: 27019
	[Token(Token = "0x400698B")]
	[FieldOffset(Offset = "0x20")]
	public static float %ed98636040bb594027eb4abaf4d0a34d5bc4d8b2;

		// Token: 0x04006994 RID: 27028
	[Token(Token = "0x4006994")]
	[FieldOffset(Offset = "0x40")]
	public static float %00365420a49d515e10e48b645eaf273e3034b035;

	*/

public:
	ConvarGraphics();
	void WriteFOV(float value);
	float GetFov();
};
