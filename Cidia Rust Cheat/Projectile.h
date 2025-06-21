#pragma once
#include "Vectors.h"
#include <Windows.h>
class Projectile
{
private:
	uintptr_t Class;
	/*
	int projectile_size;
	uintptr_t projectile_list;
	*/
	uintptr_t drag = 0x2C; // public float drag;
	uintptr_t initialVelocity = 0x20; // public Vector3 initialVelocity;
	uintptr_t gravityModifier = 0x30; // public float gravityModifier;
	uintptr_t thickness = 0x34; // public float thickness;
	uintptr_t initialDistance = 0x38; // public float initialDistance;
	uintptr_t remainInWorld = 0x3C; // public bool remainInWorld;
	uintptr_t stickProbability = 0x40; // public float stickProbability;
	uintptr_t breakProbability = 0x44; // public float breakProbability;
	uintptr_t conditionLoss = 0x48; // public float conditionLoss;
	uintptr_t ricochetChance = 0x4C; // public float ricochetChance;
	uintptr_t penetrationPower = 0x50; // public float penetrationPower;
	uintptr_t waterIntegrityLoss = 0x54; // public float waterIntegrityLoss;
	uintptr_t damageProperties = 0x58; // public DamageProperties damageProperties;
	uintptr_t damageDistances = 0x60; // public MinMax damageDistances;
	uintptr_t damageMultipliers = 0x68; // public MinMax damageMultipliers;
	uintptr_t damageTypes = 0x70; // public List<DamageTypeEntry> damageTypes;
	uintptr_t rendererToScale = 0x78; // public ScaleRenderer rendererToScale;
	uintptr_t firstPersonRenderer = 0x80; // public ScaleRenderer firstPersonRenderer;
	uintptr_t createDecals = 0x88; // public bool createDecals;
	uintptr_t doDefaultHitEffects = 0x89; // public bool doDefaultHitEffects;
	uintptr_t flybySound = 0x90; // public SoundDefinition flybySound;
	uintptr_t flybySoundDistance = 0x98; // public float flybySoundDistance;
	uintptr_t closeFlybySound = 0xA0; // public SoundDefinition closeFlybySound;
	uintptr_t closeFlybyDistance = 0xA8; // public float closeFlybyDistance;
	uintptr_t tumbleSpeed = 0xAC; // public float tumbleSpeed;
	uintptr_t tumbleAxis = 0xB0; // public Vector3 tumbleAxis;
	uintptr_t swimScale = 0xBC; // public Vector3 swimScale;
	uintptr_t swimSpeed = 0xC8; // public Vector3 swimSpeed;
	uintptr_t owner = 0xD8; // public BasePlayer owner;
	uintptr_t sourceWeaponPrefab = 0xE0; // public AttackEntity sourceWeaponPrefab;
	uintptr_t sourceProjectilePrefab = 0xE8; // public Projectile sourceProjectilePrefab;
	uintptr_t mod = 0xF0; // public ItemModProjectile mod;
	uintptr_t projectileID = 0xF8; // public int projectileID;
	uintptr_t seed = 0xFC; // public int seed;
	uintptr_t clientsideEffect = 0x100; // public bool clientsideEffect;
	uintptr_t clientsideAttack = 0x101; // public bool clientsideAttack;
	uintptr_t integrity = 0x104; // public float integrity;
	uintptr_t maxDistance = 0x108; // public float maxDistance;
	uintptr_t modifier = 0x10C; // public Projectile.Modifier modifier;
	uintptr_t invisible = 0x11C; // public bool invisible;
	uintptr_t noheadshots = 0x11D; // public bool noheadshots;
	uintptr_t currentVelocity = 0x120; // internal Vector3 currentVelocity;
	uintptr_t currentPosition = 0x12C; // internal Vector3 currentPosition;
	uintptr_t traveledDistance = 0x138; // private float traveledDistance;
	uintptr_t traveledTime = 0x13C; // private float traveledTime;
	uintptr_t launchTime = 0x140; // private float launchTime;
	uintptr_t sentPosition = 0x144; // private Vector3 sentPosition;
	uintptr_t previousPosition = 0x150; // private Vector3 previousPosition;
	uintptr_t previousVelocity = 0x15C; // private Vector3 previousVelocity;
	uintptr_t previousTraveledTime = 0x168; // private float previousTraveledTime;
	uintptr_t isUnderwater = 0x16C; // private bool isUnderwater;
	uintptr_t isRicochet = 0x16D; // private bool isRicochet;
	uintptr_t isRetiring = 0x16E; // private bool isRetiring;
	uintptr_t flybyPlayed = 0x16F; // private bool flybyPlayed;
	uintptr_t wasFacingPlayer = 0x170; // private bool wasFacingPlayer;
	uintptr_t flybyPlane = 0x174; // private Plane flybyPlane;
	uintptr_t flybyRay = 0x184; // private Ray flybyRay;
	uintptr_t cleanupAction = 0x1A0; // private Action cleanupAction;
	uintptr_t hitTest = 0x1A8; // private HitTest hitTest;
	uintptr_t swimRandom = 0x1B0; // private float swimRandom;
	uintptr_t _fleshMaterialID = 0x0; // private static uint _fleshMaterialID;
	uintptr_t _waterMaterialID = 0x4; // private static uint _waterMaterialID;
	uintptr_t cachedWaterString = 0x8; // private static uint cachedWaterString;
public:
	Projectile(uintptr_t address);
	void MoveProjectileShoot(Vector3 pos);
};