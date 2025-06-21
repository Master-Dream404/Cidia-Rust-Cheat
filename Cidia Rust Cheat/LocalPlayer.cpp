#include "LocalPlayer.h"
#include <stdio.h>
#include "driver.h"
#include <m_includes/XorStr/XR.hpp>
#include "global.h"
LocalPlayer::LocalPlayer()
{
	global::print(XR("[LocalPlayer] Initialized"));

	Class = driver::read<uint64_t>(driver::GetGameAssembly() + Class);

	global::print(XR("[LocalPlayer] LocalPlayer: 0x%llX"), Class);

	this->StaticField = driver::read<uint64_t>(Class + StaticField);
	global::print(XR("[LocalPlayer] Static Fields: 0x%llX"), StaticField);
	this->BasePlayerValue = driver::read<uint64_t>(StaticField + BasePlayerBackingField);
	global::print(XR("[LocalPlayer] Base Player: 0x%llX"), BasePlayerValue);


	//global::print(XR("maxProjectileID: %i"), driver::read<int>(BasePlayerValue + 0x89C));

}

uint64_t LocalPlayer::GetBasePlayer()
{
	return BasePlayerValue;
}

void LocalPlayer::UpdateBasePlayer()
{
	BasePlayerValue = driver::read<uint64_t>(StaticField + BasePlayerBackingField);

}

bool LocalPlayer::IsLocalPlayerValid()
{
	return BasePlayerValue != 0;
}

LocalPlayer::~LocalPlayer()
{
}