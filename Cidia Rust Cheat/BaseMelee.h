#pragma once
#include <string>
class BaseMelee
{
private:
	/*
	{
      "Address": 63083648,
      "Name": "BaseMelee_TypeInfo",
      "Signature": "BaseMelee_c*"
    },
	*/
    uint64_t helditem = 0;
    uint64_t BaseMelee_TypeInfo = 0x3C73088;
    uint64_t Class = 0;
    uint64_t damageProperties = 0x298;//public DamageProperties damageProperties;
    uint64_t damageTypes = 0x2A0;//public List<DamageTypeEntry> damageTypes;
    uint64_t maxDistance = 0x2A8;//public float maxDistance;
    uint64_t attackRadius = 0x2AC;//public float attackRadius;

    uint64_t isAutomatic = 0x2B0;//public bool isAutomatic;
    uint64_t blockSprintOnAttack = 0x2B1;//public bool blockSprintOnAttack;
    uint64_t canUntieCrates = 0x2B2;//public bool canUntieCrates;
    uint64_t longResourceForgiveness = 0x2B3;//public bool longResourceForgiveness;
    uint64_t strikeFX = 0x2B8;//public GameObjectRef strikeFX;
    uint64_t useStandardHitEffects = 0x2C0;//public bool useStandardHitEffects;
    uint64_t aiStrikeDelay = 0x2C4;//public float aiStrikeDelay;
    uint64_t swingEffect = 0x2C8;//public GameObjectRef swingEffect;
    uint64_t materialStrikeFX = 0x2D0;//public List<BaseMelee.MaterialFX> materialStrikeFX;
    uint64_t heartStress = 0x2D8;//public float heartStress;
    uint64_t gathering = 0x2E0;//public ResourceDispenser.GatherProperties gathering;
    uint64_t throwReady = 0x2E8;//private bool throwReady;
    uint64_t canThrowAsProjectile = 0x2E9;//public bool canThrowAsProjectile;
    uint64_t canAiHearIt = 0x2EA;//public bool canAiHearIt;
    uint64_t onlyThrowAsProjectile = 0x2EB;//public bool onlyThrowAsProjectile;

public:
    BaseMelee(uint64_t helditem);
    ~BaseMelee();



};