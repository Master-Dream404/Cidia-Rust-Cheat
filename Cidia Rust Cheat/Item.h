#pragma once
#include "BaseProjectile.h"
#include <memory>
#include <string>
class Item
{
	/// item class public class %eead1f60087cbc2f30ea45003245e96b04ad0491
	uint64_t Class = 0x0;
	uint64_t Info = 0x80; // Item -> public ItemDefinition info; 	public ItemDefinition %2497884e0916cdf7f76c5e32285f6131dde21f14;
	uint32_t ItemID = 0x58; // Item -> public ItemId uid; 	public ItemId %b2a5452fa6d6931602009513efcf72998b6d314b;
	uint64_t HeldEntity = 0x88; // Item -> private EntityRef heldEntity; 	private %4c3d33bdfd9e0b147602ddb7de0de0ab07a124cd %05ba3cbcb0396942c7a2551075dd6e8b02cabca8;
	std::shared_ptr<BaseProjectile> BaseProjectileInstance = nullptr;
public:
	Item(uint64_t address);
	~Item();
	uint32_t GetItemID();
	uint64_t GetHeldEntity();
	std::string GetItemName();
	std::shared_ptr<BaseProjectile> GetBaseProjectile();
	bool IsWeapon(std::string shortname, std::string* item_name_out = 0);
	std::string GetItemDisplayName(std::string shortname);
};
