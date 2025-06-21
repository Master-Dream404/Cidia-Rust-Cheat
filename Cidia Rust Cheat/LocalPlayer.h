#pragma once
#include <cstdint>
class LocalPlayer
{
	/*
	"Address": 63394872,
	 "Name": "%0491278696f8d6edababa02091d0968d7f5c51d7", - localplayer class pointer
	 "Signature": "_898ab2d7919d3055cf02682aee3afc394782f11d_c*
	*/
	uint64_t Class = 0x9E82690;
	//Dump.cs / DummyDLL
	uint64_t StaticField = 0xB8;// Static Padding To Access Static Fields
	uint64_t BasePlayerBackingField = 0x58; // private static BasePlayer <Entity>k__BackingField; private static readonly %f4fcdf85d1b93204bf773ccba340d1274c47bdaf<BasePlayer> %c16e41537e46b1260a450200fd480d2b966da4b8; // 0x58
	int64_t BasePlayerValue; // the baseplayer value
public:
	LocalPlayer();
	~LocalPlayer();
	uint64_t GetBasePlayer();
	void UpdateBasePlayer();
	bool IsLocalPlayerValid();
};
