
#include "BaseProjectile.h"
#include "driver.h"
#include <map>
#include <string>
#include "global.h"
#include "rust.h"
#include "Projectile.h"
// these are universal
std::map<uint32_t, float> OriginalRecoilPitchMin;
std::map<uint32_t, float> OriginalRecoilPitchMax;
std::map<uint32_t, float> OriginalRecoilYawMin;
std::map<uint32_t, float> OriginalRecoilYawMax;

std::map<uint32_t, float> LastRecoilY;
std::map<uint32_t, float> LastRecoilP;

std::map<uint32_t, bool> RejectedItems;
BaseProjectile::BaseProjectile(uint64_t address)
{
	//	//printf("[BaseProjectile] Initialized\n");
	this->Class = address;
	////printf("[BaseProjectile] Class: 0x%llX\n", Class);
	this->RecoilProperties = driver::read<uint64_t>(Class + RecoilProperties);
	if (RecoilProperties == 0)
		return;
	////printf("[BaseProjectile] RecoilProperties: 0x%llX\n", RecoilProperties);
	if (IsValidWeapon())
	{
		uint64_t recoiloverride = driver::read<uint64_t>(RecoilProperties + RecoilOverride);
		if (recoiloverride == 0)
			RecoilOverride = RecoilProperties; // some guns don't have a new recoil pattern and use an old one. which is located at recoilproperties instead of override
		else
			RecoilOverride = recoiloverride;
	}
}
bool BaseProjectile::IsValidWeapon()
{
	//return RecoilProperties != 0;
	if (RecoilProperties != 0)
		return true;
	else
	{
		return false;
	}
}

void BaseProjectile::WriteRecoilYaw(uint32_t itemid, int percent) {
	
/*
	if (LastRecoilY.find(itemid) == LastRecoilP.end())
	{
		LastRecoilY[itemid] = 200;//driver::read<float>(RecoilOverride + RecoilPitchMin);
	}
	else
	{
		if (LastRecoilY[itemid] != percent)
		{
			float pitchmin = OriginalRecoilYawMin[itemid];
			float pitchmax = OriginalRecoilYawMax[itemid];
			float pitchminpercent = pitchmin * (percent / 100.0f);
			float pitchmaxpercent = pitchmax * (percent / 100.0f);
			LastRecoilY[itemid] = percent;
		}
	}
*/
/*

	float yawmin = OriginalRecoilYawMin[itemid];
	float yawmax = OriginalRecoilYawMax[itemid];
	float yawminpercent = yawmin * (percent / 100.0f);
	float yawmaxpercent = yawmax * (percent / 100.0f);
	driver::write(RecoilOverride + RecoilYawMin, yawminpercent);
	driver::write(RecoilOverride + RecoilYawMax, yawmaxpercent);
*/
}


void BaseProjectile::WriteRecoilPitch(uint32_t itemid, int percent)
{

	if (LastRecoilP.find(itemid) == LastRecoilP.end())
	{
		LastRecoilP[itemid] = 200;//driver::read<float>(RecoilOverride + RecoilPitchMin);
	}
	else
	{
		if (LastRecoilP[itemid] != percent)
		{
			float pitchmin = OriginalRecoilPitchMin[itemid];
			float pitchmax = OriginalRecoilPitchMax[itemid];
			float pitchminpercent = pitchmin * (percent / 100.0f);
			float pitchmaxpercent = pitchmax * (percent / 100.0f);
			driver::write(RecoilOverride + RecoilPitchMin, pitchminpercent);
			driver::write(RecoilOverride + RecoilPitchMax, pitchmaxpercent);
			driver::write(RecoilOverride + RecoilYawMin, pitchminpercent);
			driver::write(RecoilOverride + RecoilYawMax, pitchmaxpercent);
			global::print(XR("No recoil Y"));
			global::print(XR("No recoil P"));
			LastRecoilP[itemid] = percent;
		}
	}
}

std::map<uint32_t, float> origaimCone;
std::map<uint32_t, float> orighipAimCone;
std::map<uint32_t, float> origaimConePenaltyMax;
std::map<uint32_t, float> origaimconePenaltyPerShot;
std::map<uint32_t, float> origstancePenaltyScale;
std::map<uint32_t, float> origstanceprojectileVelocityScale;
std::map<uint32_t, float> Spread;
void BaseProjectile::WriteSpread(uint32_t itemid, float percent) {
	if (origaimCone.find(itemid) == origaimCone.end())
	{
		origaimCone[itemid] = driver::read<float>(Class + aimCone);
		orighipAimCone[itemid] = driver::read<float>(Class + hipAimCone);
		origaimConePenaltyMax[itemid] = driver::read<float>(Class + aimConePenaltyMax);
		origaimconePenaltyPerShot[itemid] = driver::read<float>(Class + aimconePenaltyPerShot);
		origstancePenaltyScale[itemid] = driver::read<float>(Class + stancePenaltyScale);
		Spread[itemid] = 200;
	}

	if (Spread.find(itemid) != Spread.end())
	{
		if (percent == 100)
		{
			driver::write(Class + aimCone, origaimCone[itemid]);//aimCone
			driver::write(Class + hipAimCone, orighipAimCone[itemid]);//hipAimCone
			driver::write(Class + aimConePenaltyMax, origaimConePenaltyMax[itemid]);//aimConePenaltyMax
			driver::write(Class + aimconePenaltyPerShot, origaimconePenaltyPerShot[itemid]);//aimconePenaltyPerShot
			driver::write(Class + stancePenaltyScale, origstancePenaltyScale[itemid]);//stancePenaltyScale
		}
		else
		{
			if (percent == 0)
			{
				percent = -1.f;
			}
			if (Spread[itemid] != percent)
			{
				driver::write(Class + 0x298, 0);//aimCone
				driver::write(Class + aimCone, percent);//aimCone
				driver::write(Class + hipAimCone, percent);//hipAimCone
				driver::write(Class + aimConePenaltyMax, percent);//aimConePenaltyMax
				driver::write(Class + aimconePenaltyPerShot, percent);//aimconePenaltyPerShot
				driver::write(Class + stancePenaltyScale, percent);//stancePenaltyScale
				Spread[itemid] = percent;
				global::print(XR("No spread"));
			}
		}
	}

}

void BaseProjectile::SetBulletDrop(uint32_t itemid, float value) {

}

std::map<uint32_t, float> origreloadTime;
std::map<uint32_t, float> blockedreloadTime;
void BaseProjectile::SetReloadTime(uint32_t itemid, float time) {
	driver::write(Class + 0x344, 0);
/*
	if (origreloadTime.find(itemid) == origreloadTime.end())
	{
		origreloadTime[itemid] = driver::read<float>(Class + 0x2D0);
	}

	if (blockedreloadTime.find(itemid) == blockedreloadTime.end())
	{
		driver::write(Class + 0x2D0, 0.f);
		blockedreloadTime[itemid] = 1;
	}

	if (time > 1)
	{
		if (origreloadTime.find(itemid) != origreloadTime.end())
		{
			driver::write(Class + 0x2D0, origreloadTime[itemid]);
			blockedreloadTime.erase(itemid);
		}
	}
*/

}

std::string BaseProjectile::GetBulletName() {
	uintptr_t PrimaryMagazine = driver::read<uintptr_t>(Class + 0x2E0);//  constexpr ::std::ptrdiff_t primaryMagazine = 0x2E0; // BaseProjectile.Magazine
	uintptr_t AmmoType = driver::read<uintptr_t>(PrimaryMagazine + 0x20);//constexpr ::std::ptrdiff_t ammoType = 0x20; // ItemDefinition
	uintptr_t shortname = driver::read<uintptr_t>(AmmoType + 0x28); // shortname
	std::string result = driver::read_unicode(shortname + 0x14, 32);
	return result;
}

float BaseProjectile::GetBulletSpeed(const char* weapon_name, const char* bullet_name) {
	/* rifle ammo */

	if (_stricmp(weapon_name, XR("rifle.ak")) == NULL
		|| _stricmp(weapon_name, XR("rifle.lr300")) == NULL)
	{

		if (_stricmp(bullet_name, XR("ammo.rifle")) == NULL)
		{
			return 375.f;
		}
		if (_stricmp(bullet_name, XR("ammo.rifle.hv")) == NULL)
		{
			return 450.f;
		}
		if (_stricmp(bullet_name, XR("ammo.rifle.explosive")) == NULL)
		{
			return 225.f;
		}
		if (_stricmp(bullet_name, XR("ammo.rifle.incendiary")) == NULL)
		{
			return 225.f;
		}
	}

	if (_stricmp(weapon_name, XR("rifle.bolt")) == NULL)
	{
		if (_stricmp(bullet_name, XR("ammo.rifle")) == NULL)
		{
			return 656.f;
		}
		if (_stricmp(bullet_name, XR("ammo.rifle.hv")) == NULL)
		{
			return 788.f;
		}
		if (_stricmp(bullet_name, XR("ammo.rifle.explosive")) == NULL)
		{
			return 394.f;
		}
		if (_stricmp(bullet_name, XR("ammo.rifle.incendiary")) == NULL)
		{
			return 394.f;
		}
	}

	if (_stricmp(weapon_name, XR("rifle.l96")) == NULL)
	{
		if (_stricmp(bullet_name, XR("ammo.rifle")) == NULL)
		{
			return 1125.f;
		}
		if (_stricmp(bullet_name, XR("ammo.rifle.hv")) == NULL)
		{
			return 1350.f;
		}
		if (_stricmp(bullet_name, XR("ammo.rifle.explosive")) == NULL)
		{
			return 675.f;
		}
		if (_stricmp(bullet_name, XR("ammo.rifle.incendiary")) == NULL)
		{
			return 675.f;
		}
	}

	if (_stricmp(weapon_name, XR("rifle.m39")) == NULL)
	{
		if (_stricmp(bullet_name, XR("ammo.rifle")) == NULL)
		{
			return 469.f;
		}
		if (_stricmp(bullet_name, XR("ammo.rifle.hv")) == NULL)
		{
			return 563.f;
		}
		if (_stricmp(bullet_name, XR("ammo.rifle.explosive")) == NULL)
		{
			return 281.f;
		}
		if (_stricmp(bullet_name, XR("ammo.rifle.incendiary")) == NULL)
		{
			return 281.f;
		}
	}

	if (_stricmp(weapon_name, XR("rifle.semiauto")) == NULL)
	{
		if (_stricmp(bullet_name, XR("ammo.rifle")) == NULL)
		{
			return 375.f;
		}
		if (_stricmp(bullet_name, XR("ammo.rifle.hv")) == NULL)
		{
			return 450.f;
		}
		if (_stricmp(bullet_name, XR("ammo.rifle.explosive")) == NULL)
		{
			return 225.f;
		}
		if (_stricmp(bullet_name, XR("ammo.rifle.incendiary")) == NULL)
		{
			return 225.f;
		}
	}

	if (_stricmp(weapon_name, XR("lmg.m249")) == NULL)
	{
		if (_stricmp(bullet_name, XR("ammo.rifle")) == NULL)
		{
			return 487.5f;
		}
		if (_stricmp(bullet_name, XR("ammo.rifle.hv")) == NULL)
		{
			return 585.f;
		}
		if (_stricmp(bullet_name, XR("ammo.rifle.explosive")) == NULL)
		{
			return 293.f;
		}
		if (_stricmp(bullet_name, XR("ammo.rifle.incendiary")) == NULL)
		{
			return 293.f;
		}
	}

	/* pistol ammo */

	if (_stricmp(weapon_name, XR("smg.2")) == NULL
		|| _stricmp(weapon_name, XR("smg.mp5")) == NULL)
	{

		if (_stricmp(bullet_name, XR("ammo.pistol")) == NULL)
		{
			return 240.f;
		}
		if (_stricmp(bullet_name, XR("ammo.pistol.hv")) == NULL)
		{
			return 320.f;
		}
		if (_stricmp(bullet_name, XR("ammo.pistol.incendiary")) == NULL)
		{
			return 180.f;
		}
	}

	if (_stricmp(weapon_name, XR("pistol.m92")) == NULL
		|| _stricmp(weapon_name, XR("pistol.python")) == NULL
		|| _stricmp(weapon_name, XR("pistol.revolver")) == NULL
		|| _stricmp(weapon_name, XR("pistol.semiauto")) == NULL
		|| _stricmp(weapon_name, XR("smg.thompson")) == NULL)
	{

		if (_stricmp(bullet_name, XR("ammo.pistol")) == NULL)
		{
			return 300.f;
		}
		if (_stricmp(bullet_name, XR("ammo.pistol.hv")) == NULL)
		{
			return 400.f;
		}
		if (_stricmp(bullet_name, XR("ammo.pistol.incendiary")) == NULL)
		{
			return 225.f;
		}
	}

	/* shotgun ammo */

	if (_stricmp(weapon_name, XR("shotgun.double")) == NULL
		|| _stricmp(weapon_name, XR("shotgun.pump")) == NULL
		|| _stricmp(weapon_name, XR("shotgun.waterpipe")) == NULL
		|| _stricmp(weapon_name, XR("shotgun.spas12")) == NULL
		|| _stricmp(weapon_name, XR("pistol.eoka")) == NULL)
	{

		if (_stricmp(bullet_name, XR("ammo.shotgun.slug")) == NULL)
		{
			return 225.f;
		}
		if (_stricmp(bullet_name, XR("ammo.shotgun.fire")) == NULL)
		{
			return 100.f;
		}
		if (_stricmp(bullet_name, XR("ammo.handmade.shell")) == NULL)
		{
			return 100.f;
		}
		if (_stricmp(bullet_name, XR("ammo.shotgun.slug")) == NULL)
		{
			return 225.f;
		}
	}

	/* monkey arrows and monkey guns */

	if (_stricmp(weapon_name, XR("bow.hunting")) == NULL)
	{
		if (_stricmp(bullet_name, XR("arrow.hv")) == NULL)
		{
			return 80.f;
		}
		if (_stricmp(bullet_name, XR("arrow.bone")) == NULL)
		{
			return 45.f;
		}
		if (_stricmp(bullet_name, XR("arrow.wooden")) == NULL)
		{
			return 50.f;
		}
		if (_stricmp(bullet_name, XR("arrow.fire")) == NULL)
		{
			return 40.f;
		}
	}

	if (_stricmp(weapon_name, XR("bow.compound")) == NULL)
	{
		if (_stricmp(bullet_name, XR("arrow.hv")) == NULL)
		{
			return 160.f;
		}
		if (_stricmp(bullet_name, XR("arrow.bone")) == NULL)
		{
			return 90.f;
		}
		if (_stricmp(bullet_name, XR("arrow.wooden")) == NULL)
		{
			return 100.f;
		}
		if (_stricmp(bullet_name, XR("arrow.fire")) == NULL)
		{
			return 80.f;
		}
	}

	if (_stricmp(weapon_name, XR("crossbow")) == NULL)
	{
		if (_stricmp(bullet_name, XR("arrow.hv")) == NULL)
		{
			return 120.f;
		}
		if (_stricmp(bullet_name, XR("arrow.bone")) == NULL)
		{
			return 68.f;
		}
		if (_stricmp(bullet_name, XR("arrow.wooden")) == NULL)
		{
			return 75.f;
		}
		if (_stricmp(bullet_name, XR("arrow.fire")) == NULL)
		{
			return 60.f;
		}
	}

	if (_stricmp(weapon_name, XR("pistol.nailgun")) == NULL)
	{
		return 50.f;
	}

	return 1337.f;
}
float BaseProjectile::GetBulletGravity(const char* bullet_name) {
	if (_stricmp(bullet_name, XR("ammo.rifle")) == NULL)
	{
		return 1.f;
	}
	if (_stricmp(bullet_name, XR("ammo.rifle.hv")) == NULL)
	{
		return 1.f;
	}
	if (_stricmp(bullet_name, XR("ammo.rifle.explosive")) == NULL)
	{
		return 1.25f;
	}
	if (_stricmp(bullet_name, XR("ammo.rifle.incendiary")) == NULL)
	{
		return 1.f;
	}

	if (_stricmp(bullet_name, XR("ammo.pistol")) == NULL)
	{
		return 1.f;
	}
	if (_stricmp(bullet_name, XR("ammo.pistol.hv")) == NULL)
	{
		return 1.f;
	}
	if (_stricmp(bullet_name, XR("ammo.pistol.incendiary")) == NULL)
	{
		return 1.f;
	}

	if (_stricmp(bullet_name, XR("arrow.hv")) == NULL)
	{
		return 0.5f;
	}
	if (_stricmp(bullet_name, XR("arrow.bone")) == NULL)
	{
		return 0.75f;
	}
	if (_stricmp(bullet_name, XR("arrow.wooden")) == NULL)
	{
		return 0.75f;
	}
	if (_stricmp(bullet_name, XR("arrow.fire")) == NULL)
	{
		return 1.f;
	}

	if (_stricmp(bullet_name, XR("ammo.handmade.shell")) == NULL)
	{
		return 1.f;
	}
	if (_stricmp(bullet_name, XR("ammo.shotgun")) == NULL)
	{
		return 1.f;
	}
	if (_stricmp(bullet_name, XR("ammo.shotgun.fire")) == NULL)
	{
		return 1.f;
	}
	if (_stricmp(bullet_name, XR("ammo.shotgun.slug")) == NULL)
	{
		return 1.f;
	}

	if (_stricmp(bullet_name, XR("ammo.nailgun.nails")) == NULL)
	{
		return 0.75f;
	}

	return 1.f;
}
float BaseProjectile::GetBulletDrag(const char* bullet_name) {
	if (_stricmp(bullet_name, XR("ammo.rifle")) == NULL)
	{
		return 0.6f;
	}
	if (_stricmp(bullet_name, XR("ammo.rifle.hv")) == NULL)
	{
		return 1.f;
	}
	if (_stricmp(bullet_name, XR("ammo.rifle.explosive")) == NULL)
	{
		return 0.6f;
	}
	if (_stricmp(bullet_name, XR("ammo.rifle.incendiary")) == NULL)
	{
		return 0.6f;
	}

	if (_stricmp(bullet_name, XR("ammo.pistol")) == NULL)
	{
		return 0.7f;
	}
	if (_stricmp(bullet_name, XR("ammo.pistol.hv")) == NULL)
	{
		return 1.f;
	}
	if (_stricmp(bullet_name, XR("ammo.pistol.incendiary")) == NULL)
	{
		return 0.7f;
	}

	if (_stricmp(bullet_name, XR("arrow.hv")) == NULL)
	{
		return 0.005f;
	}
	if (_stricmp(bullet_name, XR("arrow.bone")) == NULL)
	{
		return 0.01f;
	}
	if (_stricmp(bullet_name, XR("arrow.wooden")) == NULL)
	{
		return 0.005f;
	}
	if (_stricmp(bullet_name, XR("arrow.fire")) == NULL)
	{
		return 0.01f;
	}

	if (_stricmp(bullet_name, XR("ammo.handmade.shell")) == NULL)
	{
		return 1.f;
	}
	if (_stricmp(bullet_name, XR("ammo.shotgun")) == NULL)
	{
		return 1.f;
	}
	if (_stricmp(bullet_name, XR("ammo.shotgun.fire")) == NULL)
	{
		return 1.f;
	}
	if (_stricmp(bullet_name, XR("ammo.shotgun.slug")) == NULL)
	{
		return 0.6f;
	}

	if (_stricmp(bullet_name, XR("ammo.nailgun.nails")) == NULL)
	{
		return 0.005f;
	}

	return 1.f;
}
float BaseProjectile::GetProjectileVelocityScale() {
	return driver::read<float>(Class + 0x2AC);//BaseProjectile -> projectileVelocityScale = 0x2AC; // float
}

void BaseProjectile::InstentEoka() {

	driver::write<uint8_t>(Class + successfraction, 1.f);
	/*
	if (GetAsyncKeyState(VK_LBUTTON) & 1)
	{
		driver::write<uint8_t>(Class + _didSparkThisFrame, 1);
		driver::write<uint8_t>(Class + _isStriking, 1);
	}
	else
	{
		driver::write<uint8_t>(Class + _isStriking, 0);
	}
	*/
}

void BaseProjectile::InstentCompoundBow() {
	driver::write(Class + stringHoldDurationMax, 0);
	driver::write(Class + stringBonusDamage, 1000000);
	driver::write(Class + movementPenaltyRampUpTime, 1000000);
	//global::print(XR("InstentCompoundBow"));
}

void BaseProjectile::FastBow() {
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		driver::write<bool>(Class + attackReady, true);
		global::print(XR("fast bow"));
		//driver::write<uint8_t>(Class + wasAiming, 1);
	}
	/*
	if (driver::read<bool>(Class + attackReady) == false)
	{
		driver::write(Class + attackReady, true);
	}

	if (driver::read<bool>(Class + wasAiming) == false)
	{
		driver::write(Class + attackReady, true);
		driver::write(Class + wasAiming, true);
	}
	*/
}

std::map<uint32_t, bool> Automatic;

void BaseProjectile::SetAutomatic(uint32_t itemid) {
	if (Automatic.find(itemid) == Automatic.end())
	{
		Automatic[itemid] = false;
	}
	if (Automatic.find(itemid) != Automatic.end())
	{
		if (Automatic[itemid] == false)
		{
			global::print(XR("SetAutomatic"));
			driver::write(Class + automatic, true);
			Automatic[itemid] = true;
		}
	}
}
std::map<uint32_t, bool> NoSwayObject;
void BaseProjectile::NoSway(uint32_t itemid) {
	/*
	       constexpr ::std::ptrdiff_t aimSway = 0x2F8; // float
        constexpr ::std::ptrdiff_t aimSwaySpeed = 0x2FC; // float
	*/
	if (NoSwayObject.find(itemid) == NoSwayObject.end())
	{
		driver::write(Class + 0x2F8, 0.f);
		driver::write(Class + 0x2FC, 0.f);
		NoSwayObject[itemid] = true;
	}
	else
	{
		if (NoSwayObject[itemid] == false)
		{
			driver::write(Class + 0x2F8, 0.f);
			driver::write(Class + 0x2FC, 0.f);
			NoSwayObject[itemid] = true;
		}
	}
}

void BaseProjectile::SetSimiAutomatic(uint32_t itemid) {

	if (Automatic.find(itemid) == Automatic.end())
	{
		Automatic[itemid] = true;
	}
	if (Automatic.find(itemid) != Automatic.end())
	{
		if (Automatic[itemid] == true)
		{
			global::print(XR("SetSimiAutomatic"));
			driver::write(Class + automatic, false);
			Automatic[itemid] = false;
		}
	}
}

void BaseProjectile::OverrideHitBox(Vector3 HitPoint) {
	uint64_t Projectile = driver::read<uint64_t>(Class + createdProjectiles);
	if (!Projectile) {
		//std::cout << "Failed to read Projectile" << std::endl;
		global::print(XR("Failed to read Projectile"));
		return;
	}

	size_t size = driver::read<size_t>(Projectile + 0x18);//0x18
	uint64_t List = driver::read<uint64_t>(Projectile + 0x10);//0x10
	//std::cout << "List " << List << std::endl;

	//size_t size = rust::BaseLocalPlayer->GetMaxProjectileID();//0x18
	//std::cout << "size: " << size << std::endl;

	for (int i = 0; i < size; ++i)
	{
		//std::cout << "ID: " << i << std::endl;
		uint64_t item = driver::read<uint64_t>(List + (0x20 + (i * 0x8)));
		uint64_t ht = driver::read<uint64_t>(item + hitTest);

		if (ht)
		{
			global::print(XR("Worked: %i"), i);
		}
		else
		{
			//global::print(XR("Not Worked: %i"), i);
		}
		//Sleep(10);
	}

	/*
	for (int i = 0; i < size; ++i)
	{
		//Sleep(1);
		std::cout << i << std::endl;
		uint64_t item = driver::read<uint64_t>(List + (0x20 + (i * 0x8)));
		if (!item)
		{
			//std::cout << "Failed to read item: " << i << std::endl;
			continue;
		}
		//driver::write(item + 0x108, 1000);
		uint64_t ht = driver::read<uint64_t>(item + hitTest);

		global::print(XR("SetMaxDistance"));
		driver::write(item + 0x108, 1000);
		driver::write(ht + 0x90, HitPoint);
		driver::write(ht + 0x66, 1);
		driver::write(ht + 0xB8, 698017942);
		driver::write(ht + 0xC0, "head");
		std::cout << "HitTransform overridden to head item: " << i << std::endl;
	*/

	/*
		if (!ht) {
			std::cout << "Failed to read hitTest" << std::endl;
			continue;
		}

		uint64_t HitTransform = driver::read<uint64_t>(ht + 0xB0); // public Transform HitTransform;
		if (!HitTransform) {
			std::cout << "Failed to read HitTransform" << std::endl;
			continue;
		}

		HitTransform = driver::read<uint64_t>(HitTransform + 0x10); // PTR
		if (!HitTransform) {
			std::cout << "Failed to read HitTransform PTR" << std::endl;
			continue;
		}

		uint64_t TransformObject = driver::read<uint64_t>(HitTransform + 0x30); // Object
		if (!TransformObject) {
			std::cout << "Failed to read TransformObject" << std::endl;
			continue;
		}

		uint64_t NamePointer = driver::read<uint64_t>(TransformObject + 0x60); // ObjectNamePtr
		if (!NamePointer) {
			std::cout << "Failed to read NamePointer" << std::endl;
			continue;
		}

		// Assuming NamePointer is a pointer to a char array, which holds the name of the transform.
		// Change the hitbox to "head".
		std::string HeadName = "head";
		//driver::write(NamePointer, HeadName.data()); // +1 to include null terminator
		driver::write<decltype(HeadName)>(NamePointer, HeadName.data());
		std::cout << "HitTransform overridden to head" << std::endl;
	*/

	/*
	driver::write(ht + 0x90, HitPoint);
	driver::write(ht + 0x66, 1);
	driver::write(ht + 0xB8, 698017942);
	driver::write(ht + 0xC0, "head");
	*/


//}


	

	/*
	// Optionally, you could set the hit test result to ensure it registers as a hit.
	driver::write(ht + 0x66, DidHit);
	driver::write(ht + 0x88, entity.get());
	*/

}

std::map<uint32_t, float> longhand;

void BaseProjectile::LongHand(uint32_t item_id) {
	if (longhand.find(item_id) == longhand.end())
	{
		driver::write(Class + 0x2A8, 4.5f);//BaseMelee -> public float maxDistance;
		longhand[item_id] = 4.5f;
		global::print(XR("Long hand"));
	}
}

void BaseProjectile::SetBulletThick(float value) {
	uint64_t ProjectilesList = driver::read<uint64_t>(Class + createdProjectiles);
	int size = driver::read<int>(ProjectilesList + 0x18);
	uint64_t List = driver::read<uint64_t>(ProjectilesList + 0x10);

	for (int i = 0; i < size; ++i)
	{
		uint64_t item = driver::read<uint64_t>(List + 0x20 + (i * 8));
		driver::write(item + 0x34, value);		///	public float thickness;
		global::print(XR("SetBulletThick: %f"), value);
	}

}

void BaseProjectile::SetMaxDistance(/*Vector3 pos*/) {
/*
	uint64_t ProjectilesList = driver::read<uint64_t>(Class + createdProjectiles);
	int size = driver::read<int>(ProjectilesList + 0x18);
	uint64_t List = driver::read<uint64_t>(ProjectilesList + 0x10);

	for (int i = 0; i < size; ++i)
	{
		uint64_t item = driver::read<uint64_t>(List + 0x20 + (i * 8));
		driver::write(item + 0x108, 1000);
		//driver::write(item + 0x144, pos);
		global::print(XR("SetMaxDistance"));
	}
*/
}
std::map<uint64_t, Projectile*> ProjectileClasses;
Projectile* BaseProjectile::GetProjectile() {
	uint64_t ScreatedProjectiles = driver::read<uint64_t>(Class + createdProjectiles);
	if (ProjectileClasses.find(ScreatedProjectiles) == ProjectileClasses.end())
	{
		Projectile* m_Projectile = new Projectile(ScreatedProjectiles);
		ProjectileClasses[ScreatedProjectiles] = m_Projectile;
		return m_Projectile;
	}
	else
	{
		return ProjectileClasses[ScreatedProjectiles];
	}
}

//private Vector3 sentPosition;