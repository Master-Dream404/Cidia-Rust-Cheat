#include "Item.h"
#include "driver.h"
#include <m_includes/XorStr/XR.hpp>
#include <unordered_map>
Item::Item(uint64_t address)
{

	Class = address;
	ItemID = driver::read<uint32_t>(Class + ItemID);
	HeldEntity = driver::read<uint64_t>(Class + HeldEntity);
}
Item::~Item()
{
}
uint32_t Item::GetItemID()
{
	if (Class != 0 && this != nullptr)
		return ItemID;
	else
		return 0;
}

std::string Item::GetItemName() {
	uintptr_t ItemDefinition = driver::read<uintptr_t>(Class + 0x18);
	uintptr_t shortname = driver::read<uintptr_t>(ItemDefinition + 0x28); // shortname
	std::string result = driver::read_unicode(shortname + 0x14, 32);

	if (!result.empty())
		return result;
	else
		return XR("");
}



uint64_t Item::GetHeldEntity()
{
	return HeldEntity;
}

std::shared_ptr<BaseProjectile> Item::GetBaseProjectile()
{//Projectile
	if (HeldEntity == 0)
		return nullptr;
	BaseProjectileInstance = std::make_shared<BaseProjectile>(HeldEntity);
	return BaseProjectileInstance;
}

bool Item::IsWeapon(std::string shortname, std::string* item_name_out) {
	if (shortname == XR("rifle.ak"))
	{
		*item_name_out = XR("Assault Rifle");
		return true;
	}
	if (shortname == XR("rifle.ak.ice"))
	{
		*item_name_out = XR("Assault Rifle ICE");
		return true;
	}
	if (shortname == XR("rifle.lr300"))
	{
		*item_name_out = XR("LR-300 Assault Rifle");
		return true;
	}
	if (shortname == XR("rifle.bolt"))
	{
		*item_name_out = XR("Bolt Action Rifle");
		return true;
	}
	if (shortname == XR("rifle.l96"))
	{
		*item_name_out = XR("L96 Rifle");
		return true;
	}
	if (shortname == XR("rifle.m39"))
	{
		*item_name_out = XR("M39 Rifle	");
		return true;
	}
	if (shortname == XR("rifle.semiauto"))
	{
		*item_name_out = XR("Semi Automatic Rifle");
		return true;
	}
	if (shortname == XR("lmg.m249"))
	{
		*item_name_out = XR("M249");
		return true;
	}
	if (shortname == XR("smg.2"))
	{
		*item_name_out = XR("Custom SMG");
		return true;
	}
	if (shortname == XR("smg.mp5"))
	{
		*item_name_out = XR("MP5A4");
		return true;
	}
	if (shortname == XR("pistol.m92"))
	{
		*item_name_out = XR("M92 Pistol");
		return true;
	}
	if (shortname == XR("pistol.python"))
	{
		*item_name_out = XR("Python Revolver");
		return true;
	}
	if (shortname == XR("pistol.revolver"))
	{
		*item_name_out = XR("Revolver");
		return true;
	}
	if (shortname == XR("pistol.semiauto"))
	{
		*item_name_out = XR("Semi Automatic Pistol");
		return true;
	}
	if (shortname == XR("smg.thompson"))
	{
		*item_name_out = XR("Thompson");
		return true;
	}
	if (shortname == XR("shotgun.double"))
	{
		*item_name_out = XR("Double Barrel Shotgun");
		return true;
	}
	if (shortname == XR("shotgun.pump"))
	{
		*item_name_out = XR("Pump Shotgun");
		return true;
	}
	if (shortname == XR("shotgun.waterpipe"))
	{
		*item_name_out = XR("Waterpipe Shotgun");
		return true;
	}
	if (shortname == XR("shotgun.spas12"))
	{
		*item_name_out = XR("Spas-12 Shotgun");
		return true;
	}
	if (shortname == XR("pistol.eoka"))
	{
		*item_name_out = XR("Eoka Pistol");
		return true;
	}
	if (shortname == XR("bow.hunting"))
	{
		*item_name_out = XR("Hunting Bow");
		return true;
	}
	if (shortname == XR("bow.compound"))
	{
		*item_name_out = XR("Compound Bow");
		return true;
	}
	if (shortname == XR("crossbow"))
	{
		*item_name_out = XR("Crossbow");
		return true;
	}
	if (shortname == XR("pistol.nailgun"))
	{
		*item_name_out = XR("Nailgun");
		return true;
	}
	return false;
}

std::string Item::GetItemDisplayName(std::string shortname) {
    static std::unordered_map<std::string, std::string> itemNames = {
        // Weapons
        {"rifle.ak", "Assault Rifle"},
        {"rifle.ak.ice", "Assault Rifle ICE"},
        {"rifle.lr300", "LR-300 Assault Rifle"},
        {"rifle.bolt", "Bolt Action Rifle"},
        {"rifle.l96", "L96 Rifle"},
        {"rifle.m39", "M39 Rifle"},
        {"rifle.semiauto", "Semi Automatic Rifle"},
        {"lmg.m249", "M249"},
        {"smg.2", "Custom SMG"},
        {"smg.mp5", "MP5A4"},
        {"pistol.m92", "M92 Pistol"},
        {"pistol.python", "Python Revolver"},
        {"pistol.revolver", "Revolver"},
        {"pistol.semiauto", "Semi Automatic Pistol"},
        {"smg.thompson", "Thompson"},
        {"shotgun.double", "Double Barrel Shotgun"},
        {"shotgun.pump", "Pump Shotgun"},
        {"shotgun.waterpipe", "Waterpipe Shotgun"},
        {"shotgun.spas12", "Spas-12 Shotgun"},
        {"pistol.eoka", "Eoka Pistol"},
        {"bow.hunting", "Hunting Bow"},
        {"bow.compound", "Compound Bow"},
        {"crossbow", "Crossbow"},
        {"pistol.nailgun", "Nailgun"},
        // Ammunition
        {"ammo.handmade.shell", "12 Gauge Buckshot"},
        {"ammo.pistol", "Pistol Bullet"},
        {"ammo.pistol.fire", "Incendiary Pistol Bullet"},
        {"ammo.rifle", "5.56 Rifle Ammo"},
        {"ammo.rifle.explosive", "Explosive 5.56 Rifle Ammo"},
        {"ammo.rifle.hv", "HV 5.56 Rifle Ammo"},
        {"ammo.rocket.basic", "Rocket"},
        {"ammo.rocket.fire", "Incendiary Rocket"},
        {"ammo.rocket.hv", "HV Rocket"},
        {"ammo.shotgun", "12 Gauge Slug"},
        {"ammo.shotgun.fire", "Incendiary 12 Gauge Slug"},
        {"ammo.shotgun.slug", "12 Gauge Slug"},
        // Resources
        {"apple", "Apple"},
        {"banana", "Banana"},
        {"blueberries", "Blueberries"},
        {"chocolate", "Chocolate"},
        {"coconut", "Coconut"},
        {"corn", "Corn"},
        {"fish.troutsmall", "Small Trout"},
        {"fish.troutsmall.cooked", "Cooked Small Trout"},
        {"granolabar", "Granola Bar"},
        {"mushroom", "Mushroom"},
        {"pumpkin", "Pumpkin"},
        {"scrap", "Scrap"},
        {"water", "Water"},
        {"wolfmeat.burned", "Burned Wolf Meat"},
        {"wolfmeat.cooked", "Cooked Wolf Meat"},
        {"wolfmeat.raw", "Raw Wolf Meat"},
        {"wood", "Wood"},
        {"ore", "Ore"},
        {"ore.sulfur", "Sulfur Ore"},
        {"ore.metal", "Metal Ore"},
        // Tools
        {"hammer", "Hammer"},
        {"jackolantern.angry", "Angry Jack O Lantern"},
        {"jackolantern.happy", "Happy Jack O Lantern"},
        {"knife.bone", "Bone Knife"},
        {"knife.butcher", "Butcher Knife"},
        {"lantern", "Lantern"},
        {"lockpad", "Code Lock"},
        {"map", "Map"},
        {"note", "Note"},
        {"paper", "Paper"},
        {"pickaxe", "Pickaxe"},
        {"rock", "Rock"},
        {"torch", "Torch"},
        {"targeting.computer", "Targeting Computer"},
        // Clothing
        {"clothes.burlap.boots", "Burlap Shoes"},
        {"clothes.burlap.gloves", "Burlap Gloves"},
        {"clothes.burlap.headwrap", "Burlap Headwrap"},
        {"clothes.burlap.shirt", "Burlap Shirt"},
        {"clothes.burlap.tshirt", "Burlap T-Shirt"},
        {"clothes.burlap.trousers", "Burlap Trousers"},
        {"clothes.hide.boots", "Hide Boots"},
        {"clothes.hide.poncho", "Hide Poncho"},
        {"clothes.hide.skirt", "Hide Skirt"},
        {"clothes.hide.vest", "Hide Vest"},
        {"clothes.jacket", "Jacket"},
        {"clothes.jacket.snow", "Snow Jacket"},
        {"clothes.pants", "Pants"},
        {"clothes.pants.shorts", "Shorts"},
        {"clothes.shirt", "Shirt"},
        {"clothes.shirt.tanktop", "Tank Top"},
        {"wood.armor.jacket", "Wood Armor"},
        {"wood.armor.pants", "Wood Armor Pants"},
        // Misc
        {"apple.spoiled", "Spoiled Apple"},
        {"bandage", "Bandage"},
        {"bucket.water", "Water Bucket"},
        {"bota.bag", "Water Jug"},
        {"blueprints.base", "Blueprints"},
        {"cactusflesh", "Cactus Flesh"},
        {"can.beans.empty", "Empty Can of Beans"},
        {"can.beans", "Can of Beans"},
        {"can.tuna.empty", "Empty Tuna Can"},
        {"can.tuna", "Tuna Can"},
        {"charcoal", "Charcoal"},
        {"cloth", "Cloth"},
        {"glue", "Glue"},
        {"gunpowder", "Gun Powder"},
        {"hide", "Animal Hide"},
        {"hq.metal.ore", "High Quality Metal Ore"},
        {"metal.fragments", "Metal Fragments"},
        {"metal.ore", "Metal Ore"},
        {"metal.refined", "High Quality Metal"},
        {"metalblade", "Metal Blade"},
        {"metalpipe", "Metal Pipe"},
        {"propanetank", "Propane Tank"},
        {"resin", "Resin"},
        {"rope", "Rope"},
        {"scrap.hq", "High Quality Metal"},
        {"skull.human", "Human Skull"},
        {"skull.wolf", "Wolf Skull"},
        {"stones", "Stones"},
        {"sulfur", "Sulfur"},
        {"sulfur.ore", "Sulfur Ore"},
        {"tarp", "Tarp"},
        {"techparts", "Tech Trash"},
        {"empty.propane.tank", "Empty Propane Tank"},
        {"wolfmeat.burned", "Burned Wolf Meat"},
        {"wolfmeat.cooked", "Cooked Wolf Meat"},
        {"wolfmeat.raw", "Raw Wolf Meat"},
        {"xmas.present.large", "Large Present"},
        {"xmas.present.medium", "Medium Present"},
        {"xmas.present.small", "Small Present"},
        {"yule.log", "Yule Log"},
        {"small.medkit", "Small Medkit"},
        {"large.medkit", "Large Medkit"},
        {"medkit", "Medkit"},
        {"can.beans", "Can of Beans"},
        {"smg", "Mp5"},
        {"jackolantern.angry", "Jack O'Lantern"},
        {"hat.beenie", "Beenie Hat"},
        {"hat.boonie", "Boonie Hat"},
        {"hat.candle", "Candle Hat"},
        {"hat.cap", "Cap"},
        {"hat.coffeecan", "Coffee Can Helmet"},
        {"hat.miner", "Miner's Hat"},
        {"hat.wolf", "Wolf Headdress"},
        {"riot.face.mask", "Riot Helmet"},
        {"shirt.tanktop", "Tank Top"},
        {"shirt.collared", "Collared Shirt"},
        {"shirt.long", "Longsleeve T-Shirt"},
        {"shirt.short", "T-Shirt"},
        {"pants", "Pants"},
        {"pants.shorts", "Shorts"},
        {"skirt", "Skirt"},
        {"jacket", "Jacket"},
        {"jacket.puffy", "Puffy Jacket"},
        {"jacket.hoodie", "Hoodie"},
        {"hoodie", "Hoodie"},
        {"hoodie", "Hoodie"},
        {"gloves.leather", "Leather Gloves"},
        {"gloves.work", "Work Gloves"},
        {"boots", "Boots"},
        {"sandals", "Sandals"},
        {"boots.fur", "Fur Boots"},
        {"hazmat.jacket", "Hazmat Jacket"},
        {"hazmat.pants", "Hazmat Suit"},
        {"hazmat.gloves", "Hazmat Gloves"},
        {"hazmat.boots", "Hazmat Boots"},
        {"hazmat.mask", "Hazmat Mask"},
        {"sign.wooden.huge", "Large Wooden Sign"},
        {"sign.wooden.large", "Wooden Sign"},
        {"sign.wooden.medium", "Medium Wooden Sign"},
        {"sign.pictureframe.landscape", "Landscape Picture Frame"},
        { "sign.pictureframe.portrait", "Portrait Picture Frame" },
        { "sign.pictureframe.tall", "Tall Picture Frame" },
        { "sign.pictureframe.xl", "XL Picture Frame" },
        { "sign.pictureframe.xxl", "XXL Picture Frame" },
        { "sign.pole.banner.large", "Large Banner Hanging" },
        { "sign.pole.banner.medium", "Medium Banner Hanging" },
        { "sign.pole.banner.small", "Small Banner Hanging" },
        { "sign.post.double", "Double Sign Post" },
        { "sign.post.single", "Single Sign Post" },
        { "spinner.wheel", "Spinning Wheel" },
        { "stash.small", "Small Stash" },
        { "stash.large", "Large Wooden Box" },
        { "tool.camera", "Camera" },
        { "tool.binoculars", "Binoculars" },
        { "tool.grinder", "Grinder" },
        { "tool.hatchet", "Stone Hatchet" },
        { "tool.icepick", "Icepick" },
        { "tool.lantern", "Lantern" },
        { "tool.laptop", "Laptop" },
        { "tool.icepick", "Icepick" },
        { "tool.lantern", "Lantern" },
        { "tool.laptop", "Laptop" },
        { "tool.research", "Research Table" },
        { "tool.rock", "Rock" },
        { "tool.salvaged.sword", "Salvaged Sword" },
        { "tool.searchlight", "Search Light" },
        { "tool.sledgehammer", "Sledgehammer" },
        { "tool.wrench", "Wrench" },
        { "trap.bear", "Bear Trap" },
        { "trap.landmine", "Land Mine" },
        { "trap.landmine.concrete", "Concrete Barricade" },
        { "trap.spike.wall", "Wooden Spike Wall" },
        { "trap.spikes.floor", "Wooden Floor Spikes" },
        { "trap.spring", "Spring Trap" },
        { "tshirt", "T-Shirt" },
        { "wetsuit", "Wetsuit" },
        { "pants", "Pants" },
        { "booniehat", "Boonie Hat" },
        { "burlap.headwrap", "Burlap Headwrap" },
        { "bucket.water", "Water Bucket" },
        { "burlap.headwrap", "Burlap Headwrap" },
        { "bucket.water", "Water Bucket" },
        { "burlap.shoes", "Burlap Shoes" },
        { "burlap.trousers", "Burlap Trousers" },
        { "cactusflesh", "Cactus Flesh" },
        { "campfire", "Camp Fire" },
        { "candycane", "Candy Cane" },
        { "candycane", "Candy Cane" },
        { "chainsaw", "Chainsaw" },
        { "charcoal", "Charcoal" },
        { "chicken.burned", "Burned Chicken" },
        { "chicken.cooked", "Cooked Chicken" },
        { "chicken.raw", "Raw Chicken" },
        { "chicken.spoiled", "Spoiled Chicken" },
        { "christmastree", "Christmas Tree" },
        { "clone.cutter", "Clone" },
        { "clone.rifle", "Rifle" },
        { "clone.station", "Cloning Facility" },
        { "clutterpile", "Clutter Pile" },
        { "coal", "Coal" },
        { "compass", "Compass" },
        { "computerstation", "Computer Station" },
        { "copper", "Copper" },
        { "corn", "Corn" },
        { "crate_normal", "Crate" },
        { "crate_normal", "Crate" },
        { "crate_tools", "Tool Crate" },
        { "crossbow", "Crossbow" },
        { "cuttingplant", "Cutting Plant" },
        { "diving.mask", "Diving Mask" },
        { "diving.tank", "Diving Tank" },
        { "diving.wetsuit", "Diving Wetsuit" },
        { "door.double.hinged.metal", "Armored Double Door" },
        { "door.double.hinged.toptier", "High External Wooden Gate" },
        { "door.double.hinged.wood", "Wood Double Door" },
        { "door.hinged.metal", "Sheet Metal Door" },
        { "door.hinged.toptier", "High External Wooden Wall" },
        { "door.hinged.wood", "Wooden Door" },
        { "door.key", "Key Lock" },
        { "door.rustjail", "Prison Cell Gate" },
        { "electric.andswitch", "Electrical Branch" },
        { "electric.blocker", "Electric Blocker" },
        { "electric.booster", "Root Combiner" },
        { "electric.burnt", "Burnt Out" },
        { "electric.counter", "Electric Counter" },
        { "electric.doorcontroller", "Door Controller" },
        { "electric.egenerator", "Electric Generator" },
        { "electric.fuelhandler", "Large Generator" },
        { "electric.guitar", "Electric Guitar" },
        { "electric.hbhf", "HBHF Sensor" },
        { "electric.laserdetector", "Laser Detector" },
        { "electric.lightsensor", "Light Sensor" },
        { "electric.memorycell", "Memory Cell" },
        { "electric.motherboard", "Motherboard" },
        { "electric.rfbroadcast", "RF Broadcaster" },
        { "electric.rootcombiner", "Root Combiner" },
        { "electric.rootswitch", "Root Switch" },
        { "electric.splitters", "Electrical Branch" },
        { "electric.splitters", "Electrical Branch" },
        { "electric.splitter", "Electrical Branch" },
        { "electric.splitter", "Electrical Branch" },
        { "electric.switch", "Electrical Branch" },
        { "electric.switch", "Electrical Branch" },
        { "electric.timer", "Timer" },
        { "electric.xlgates", "Large Water Catcher" },
        { "electric.xlpipes", "Large Water Catcher" },
        { "electric.xlpipes", "Large Water Catcher" },
        { "empty.propanetank", "Empty Propane Tank" },
        { "emptycannister", "Empty Can of Beans" },
        { "emptysoda", "Empty Tuna Can" },
        { "falling.leaves", "Falling Leaves" },
        { "fish.cooked", "Cooked Fish" },
        { "fish.raw", "Raw Fish" },
        { "fish.troutsmall.cooked", "Cooked Small Trout" },
        { "fish.troutsmall.raw", "Small Trout" },
        { "flamethrower", "Flamethrower" },
        { "food.boiled.burned", "Burned Boiled Egg" },
        { "food.boiled.cooked", "Boiled Egg" },
        { "food.boiled.raw", "Raw Boiled Egg" },
        { "food.burned", "Burned Bacon" },
        { "food.candybar", "Chocolate Bar" },
        { "food.cooked", "Cooked Bear Meat" },
        { "food.cooked", "Cooked Chicken" },
        { "food.cooked", "Cooked Deer Meat" },
        { "food.cooked", "Cooked Horse Meat" },
        { "food.cooked", "Cooked Human Meat" },
        { "food.cooked", "Cooked Pork" },
        { "food.cooked", "Cooked Wolf Meat" },
        { "food.fish", "Raw Fish" },
        { "food.fish.cooked", "Cooked Fish" },
        { "food.fish.raw", "Raw Fish" },
        { "food.humanmeat.burned", "Burned Human Meat" },
        { "food.humanmeat.cooked", "Cooked Human Meat" },
        { "food.humanmeat.raw", "Raw Human Meat" },
        { "food.oil", "Cooked Bear Meat" },
        { "food.oil", "Cooked Chicken" },
        { "food.oil", "Cooked Deer Meat" },
        { "food.oil", "Cooked Horse Meat" },
        { "food.oil", "Cooked Human Meat" },
        { "food.oil", "Cooked Pork" },
        { "food.oil", "Cooked Wolf Meat" },
        { "food.pork.cooked", "Cooked Pork" },
        { "food.pork.raw", "Raw Pork" },
        { "food.raw", "Raw Bear Meat" },
        { "food.raw", "Raw Chicken" },
        { "food.raw", "Raw Deer Meat" },
        { "food.raw", "Raw Fish" },
        { "food.raw", "Raw Horse Meat" },
        { "food.raw", "Raw Human Meat" },
        { "food.raw", "Raw Pork" },
        { "food.raw", "Raw Wolf Meat" },
        { "food.spoiled", "Spoiled Bacon" },
        { "food.spoiled", "Spoiled Bear Meat" },
        { "food.spoiled", "Spoiled Chicken" },
        { "food.spoiled", "Spoiled Deer Meat" },
        { "food.spoiled", "Spoiled Horse Meat" },
        { "food.spoiled", "Spoiled Human Meat" },
        { "food.spoiled", "Spoiled Pork" },
        { "food.spoiled", "Spoiled Wolf Meat" },
        { "fuel.lowgrade", "Low Grade Fuel" },
        { "fun.arrowsign", "Arrow Sign" },
        { "fun.arrowsign.large", "Large Arrow Sign" },
        { "fun.arrowsign.medium", "Medium Arrow Sign" },
        { "fun.arrowsign.small", "Small Arrow Sign" },
        { "fun.armchair", "Arm Chair" },
        { "fun.armchair", "Arm Chair" },
        { "fun.armorstand", "Armor Stand" },
        { "fun.arcade", "Arcade Game" },
        { "fun.balloon", "Balloon" },
        { "fun.barrelrace", "Barrel Race" },
    };

    if (itemNames.find(shortname) != itemNames.end())
    {
        return itemNames[shortname];
    }
    else
    {
        return shortname;
    }
}