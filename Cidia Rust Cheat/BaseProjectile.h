#pragma once
#include <cstdint>
#include <string>
#include <Windows.h>
#include "Vectors.h"
class BasePlayer;
class Projectile;
class BaseProjectile
{
	/*
		driver::write(Class + 0x310, 0.f);//aimCone
		driver::write(Class + 0x314, 0.f);//hipAimCone
		driver::write(Class + 0x31C, 0.f);//aimConePenaltyMax
		driver::write(Class + 0x318, 0.f);//aimconePenaltyPerShot
		driver::write(Class + 0x328, 0.f);//stancePenaltyScale
	*/
	uint64_t Class = 0x0;
	uint64_t RecoilProperties = 0x300; //	public RecoilProperties recoil;

	// Part of  RecoilProperties
	uint64_t RecoilOverride = 0x310; // RecoilProperties-> public RecoilProperties newRecoilOverride;
	uint64_t RecoilYawMin = 0x18; // RecoilProperties-> public float recoilYawMin;
	uint64_t RecoilYawMax = 0x1C; //  RecoilProperties-> public float recoilYawMax;
	uint64_t RecoilPitchMin = 0x20; // RecoilProperties-> public float recoilPitchMin;
	uint64_t RecoilPitchMax = 0x24; // RecoilProperties-> public float recoilPitchMax;
	uint64_t ProjectileThickness = 0x34; // Projectile-> public float thickness;

	uint64_t aimCone = 0x320; //BaseProjectile  -> aimCone
	uint64_t hipAimCone = 0x324; //BaseProjectile  -> hipAimCone
	uint64_t aimConePenaltyMax = 0x32C; //BaseProjectile  -> aimConePenaltyMax
	uint64_t aimconePenaltyPerShot = 0x328; //BaseProjectile  -> aimconePenaltyPerShot
	uint64_t stancePenaltyScale = 0x338; //BaseProjectile  -> stancePenaltyScale

	uint64_t projectileVelocityScale = 0x2BC;//BaseProjectile -> projectileVelocityScale // float

	uint64_t automatic = 0x2B0;

	/// FlintStrikeWeapon
	uint64_t successfraction = 0x3A8;
	uint64_t successIncrease = 0x3AC;
	uint64_t strikeRecoil = 0x3B0;//public RecoilProperties strikeRecoil;
	uint64_t _didSparkThisFrame = 0x3B8;
	uint64_t _isStriking = 0x3B9;
	uint64_t strikes = 0x3BC;

	///public class BowWeapon : global::BaseProjectile
	uint64_t attackReady = 0x3A8;
	uint64_t wasAiming = 0x3B8;

	///public class CompoundBowWeapon : BowWeapon
	uint64_t stringHoldDurationMax = 0x3C0;
	uint64_t stringBonusDamage = 0x3C4;
	uint64_t movementPenaltyRampUpTime = 0x3D0;

	//uint64_t maxDistance = 


	///Projectile

	//  constexpr ::std::ptrdiff_t createdProjectiles = 0x3A8; // List<Projectile>
	uint64_t createdProjectiles = 0x3A8;// List<Projectile> 	private static readonly %f4fcdf85d1b93204bf773ccba340d1274c47bdaf<List<Projectile>> %1e153bcad5545dcecc537c2d5223c29dc09f7321;

	uint64_t hitTest = 0x1A8;// HitTest

public:
	BaseProjectile(uint64_t address);
	bool IsValidWeapon();
	void WriteRecoilYaw(uint32_t itemid, int percent);
	void WriteRecoilPitch(uint32_t itemid, int percent);
	void WriteSpread(uint32_t itemid, float percent/*float newSpread*/);
	void SetReloadTime(uint32_t itemid, float time);
	void SetBulletDrop(uint32_t itemid, float value);
	std::string GetBulletName();
	float GetBulletSpeed(const char* weapon_name, const char* bullet_name);
	float GetBulletGravity(const char* bullet_name);
	float GetBulletDrag(const char* bullet_name);
	float GetProjectileVelocityScale();
	void InstentEoka();
	void InstentCompoundBow();
	void FastBow();
	void SetSimiAutomatic(uint32_t itemid);
	void SetAutomatic(uint32_t itemid);
	void NoSway(uint32_t itemid);
	void OverrideHitBox(Vector3 HitPoint);
	void LongHand(uint32_t item_id);
	void SetBulletThick(float value);
	void SetMaxDistance(/*Vector3 pos*/);
	Projectile* GetProjectile();
};
