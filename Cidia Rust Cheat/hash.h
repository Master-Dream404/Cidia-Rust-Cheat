#pragma once
#include <string>
#include <m_includes/XorStr/XR.hpp>
#include <map>

std::map<std::string, std::string> ObjectsNames;


bool alf = false;
void LoadObjectNames() {
	if (!alf)
	{
		global::print(XR("assets loaded"));
		ObjectsNames[XR("assets/prefabs/misc/orebonus/orebonus_generic.prefab")] = XR("Hot Spot");
		ObjectsNames[XR("assets/bundled/prefabs/autospawn/resource/ores/metal-ore.prefab")] = XR("Metal Ore");
		ObjectsNames[XR("assets/bundled/prefabs/radtown/ore_metal.prefab")] = XR("Metal Ore");
		ObjectsNames[XR("assets/bundled/prefabs/autospawn/resource/ores_snow/metal-ore.prefab")] = XR("Metal Ore");
		ObjectsNames[XR("assets/bundled/prefabs/autospawn/resource/ores/sulfur-ore.prefab")] = XR("Sulfur Ore");
		ObjectsNames[XR("assets/bundled/prefabs/radtown/ore_sulfur.prefab")] = XR("Sulfur Ore");
		ObjectsNames[XR("assets/bundled/prefabs/autospawn/resource/ores_snow/sulfur-ore.prefab")] = XR("Sulfur Ore");
		ObjectsNames[XR("assets/bundled/prefabs/autospawn/resource/ores/stone-ore.prefab")] = XR("Stone Ore");
		ObjectsNames[XR("assets/bundled/prefabs/radtown/ore_stone.prefab")] = XR("Stone Ore");
		ObjectsNames[XR("assets/bundled/prefabs/autospawn/resource/ores_snow/stone-ore.prefab")] = XR("Stone Ore");


		ObjectsNames[XR("assets/bundled/prefabs/radtown/loot_barrel_2.prefab")] = XR("Loot Barrel");
		ObjectsNames[XR("assets/bundled/prefabs/radtown/loot_barrel_1.prefab")] = XR("Loot Barrel");
		ObjectsNames[XR("assets/bundled/prefabs/autospawn/resource/loot/loot-barrel-1.prefab")] = XR("Loot Barrel");
		ObjectsNames[XR("assets/bundled/prefabs/autospawn/resource/loot/loot-barrel-2.prefab")] = XR("Loot Barrel");
		ObjectsNames[XR("assets/bundled/prefabs/radtown/oil_barrel.prefab")] = XR("Oil Barrel");


		ObjectsNames[XR("assets/bundled/prefabs/radtown/underwater_labs/crate_ammunition.prefab")] = XR("Ammunition Crate");
		ObjectsNames[XR("assets/bundled/prefabs/radtown/crate_basic.prefab")] = XR("Loot Crate");
		ObjectsNames[XR("assets/bundled/prefabs/radtown/foodbox.prefab")] = XR("Food Box");
		ObjectsNames[XR("assets/bundled/prefabs/radtown/underwater_labs/crate_food_1.prefab")] = XR("Food Crate");
		ObjectsNames[XR("assets/bundled/prefabs/radtown/underwater_labs/crate_food_2.prefab")] = XR("Food Crate");
		ObjectsNames[XR("assets/bundled/prefabs/radtown/crate_normal_2_food.prefab")] = XR("Food Crate");
		ObjectsNames[XR("assets/bundled/prefabs/radtown/underwater_labs/crate_fuel.prefab")] = XR("Fuel Crate");
		ObjectsNames[XR("assets/bundled/prefabs/radtown/underwater_labs/crate_medical.prefab")] = XR("Medical Crate");
		ObjectsNames[XR("assets/bundled/prefabs/radtown/crate_normal_2_medical.prefab")] = XR("Medical Crate");
		ObjectsNames[XR("assets/bundled/prefabs/radtown/crate_mine.prefab")] = XR("Mine Crate");
		ObjectsNames[XR("assets/bundled/prefabs/radtown/crate_normal.prefab")] = XR("Military Crate");
		ObjectsNames[XR("assets/prefabs/npc/m2bradley/bradley_crate.prefab")] = XR("APC Crate");
		ObjectsNames[XR("assets/bundled/prefabs/radtown/underwater_labs/crate_normal.prefab")] = XR("Loot Crate");
		ObjectsNames[XR("assets/bundled/prefabs/radtown/crate_normal_2.prefab")] = XR("Loot Crate");
		ObjectsNames[XR("assets/bundled/prefabs/radtown/underwater_labs/crate_normal_2.prefab")] = XR("Loot Crate");
		ObjectsNames[XR("assets/bundled/prefabs/radtown/crate_tools.prefab")] = XR("Tools Crate");
		ObjectsNames[XR("assets/prefabs/npc/patrol helicopter/heli_crate.prefab")] = XR("Heli Crate");
		ObjectsNames[XR("assets/prefabs/misc/supply drop/supply_drop.prefab")] = XR("Supply Drop");
		ObjectsNames[XR("assets/bundled/prefabs/radtown/vehicle_parts.prefab")] = XR("Vehicle Parts");
		ObjectsNames[XR("assets/prefabs/misc/item drop/item_drop_backpack.prefab")] = XR("Back Pack");

		ObjectsNames[XR("assets/bundled/prefabs/autospawn/collectable/hemp/hemp-collectable.prefab")] = XR("Hemp");
		ObjectsNames[XR("assets/bundled/prefabs/autospawn/collectable/mushrooms/mushroom-cluster-6.prefab")] = XR("Mushroom Cluster");
		ObjectsNames[XR("assets/bundled/prefabs/autospawn/collectable/pumpkin/pumpkin-collectable.prefab")] = XR("Pumpkin");
		ObjectsNames[XR("assets/bundled/prefabs/autospawn/collectable/corn/corn-collectable.prefab")] = XR("Corn");
		ObjectsNames[XR("assets/bundled/prefabs/autospawn/collectable/berry-white/berry-white-collectable.prefab")] = XR("Berry");
		ObjectsNames[XR("assets/bundled/prefabs/autospawn/collectable/potato/potato-collectable.prefab")] = XR("Potato");
		ObjectsNames[XR("assets/bundled/prefabs/autospawn/collectable/stone/sulfur-collectable.prefab")] = XR("Sulfur Collectable");
		ObjectsNames[XR("assets/bundled/prefabs/autospawn/collectable/stone/stone-collectable.prefab")] = XR("Stone Collectable");
		ObjectsNames[XR("assets/bundled/prefabs/autospawn/collectable/wood/wood-collectable.prefab")] = XR("Wood Collectable");
		ObjectsNames[XR("assets/bundled/prefabs/autospawn/collectable/stone/metal-collectable.prefab")] = XR("Metal Collectable");
		ObjectsNames[XR("assets/rust.ai/agents/bear/bear.prefab")] = XR("Bear");
		ObjectsNames[XR("assets/rust.ai/agents/boar/boar.prefab")] = XR("Boar");
		ObjectsNames[XR("assets/rust.ai/agents/chicken/chicken.prefab")] = XR("Chicken");
		ObjectsNames[XR("assets/rust.ai/agents/horse/horse.prefab")] = XR("Horse");
		ObjectsNames[XR("assets/rust.ai/agents/stag/stag.prefab")] = XR("Stag");
		ObjectsNames[XR("assets/rust.ai/agents/wolf/wolf.prefab")] = XR("Wolf");
		ObjectsNames[XR("assets/rust.ai/agents/zombie/zombie.prefab")] = XR("Zombie");

		ObjectsNames[XR("assets/content/vehicles/minicopter/minicopter.entity.prefab")] = XR("MiniCopter");
		ObjectsNames[XR("assets/content/vehicles/scrap heli carrier/scraptransporthelicopter.prefab")] = XR("Scrap Transport Helicopter");
		ObjectsNames[XR("assets/prefabs/npc/m2bradley/bradleyapc.prefab")] = XR("APC");
		ObjectsNames[XR("assets/prefabs/npc/patrol helicopter/patrolhelicopter.prefab")] = XR("Patrol Helicopter");

		ObjectsNames[XR("assets/content/vehicles/boats/rhib/rhib.prefab")] = XR("RHIB");
		ObjectsNames[XR("assets/rust.ai/nextai/testridablehorse.prefab")] = XR("Horse");
		ObjectsNames[XR("assets/prefabs/npc/autoturret/autoturret_deployed.prefab")] = XR("AutoTurret");
		ObjectsNames[XR("assets/prefabs/npc/sam_site_turret/sam_site_turret_deployed.prefab")] = XR("Sam Site");
		ObjectsNames[XR("assets/prefabs/npc/sam_site_turret/sam_static.prefab")] = XR("Sam Site");
		ObjectsNames[XR("assets/prefabs/deployable/landmine/landmine.prefab")] = XR("Landmine");
		ObjectsNames[XR("assets/prefabs/deployable/bear trap/beartrap.prefab")] = XR("BearTrap");
		ObjectsNames[XR("assets/prefabs/deployable/single shot trap/guntrap.deployed.prefab")] = XR("GunTrap");
		ObjectsNames[XR("assets/prefabs/npc/flame turret/flameturret.deployed.prefab")] = XR("FlameTurret");
		ObjectsNames[XR("assets/prefabs/deployable/sleeping bag/sleepingbag_leather_deployed.prefab")] = XR("SleepingBag");
		ObjectsNames[XR("assets/prefabs/misc/item drop/item_drop.prefab")] = XR("Item");
		ObjectsNames[XR("assets/prefabs/misc/burlap sack/generic_world.prefab")] = XR("Dropped item");

		ObjectsNames[XR("assets/prefabs/tools/c4/explosive.timed.deployed.prefab")] = XR("C4");
		ObjectsNames[XR("assets/prefabs/tools/c4/explosive.timed.entity.prefab")] = XR("C4");

		ObjectsNames[XR("assets/prefabs/weapons/satchelcharge/explosive.satchel.deployed.prefab")] = XR("Satchel");
		ObjectsNames[XR("assets/prefabs/weapons/satchelcharge/explosive.satchel.entity.prefab")] = XR("Satchel");

		ObjectsNames[XR("assets/prefabs/ammo/rocket/rocket_basic.prefab")] = XR("Rocket");
		ObjectsNames[XR("assets/prefabs/ammo/rocket/rocket_fire.prefab")] = XR("Fire Rocket");
		ObjectsNames[XR("assets/prefabs/ammo/rocket/rocket_hv.prefab")] = XR("HV Rocket");

		ObjectsNames[XR("assets/prefabs/deployable/tool cupboard/cupboard.tool.deployed.prefab")] = XR("TC");
		ObjectsNames[XR("assets/prefabs/deployable/tool cupboard/retro/cupboard.tool.retro.deployed.prefab")] = XR("TC");

		ObjectsNames[XR("assets/prefabs/deployable/large wood storage/box.wooden.large.prefab")] = XR("Large Wood Storage");
		ObjectsNames[XR("assets/prefabs/deployable/furnace.large/furnace.large.prefab")] = XR("Large Furnace");
		ObjectsNames[XR("assets/prefabs/deployable/furnace/furnace.prefab")] = XR("Furnace");

		ObjectsNames[XR("assets/prefabs/deployable/playerioents/batteries/large/large.rechargable.battery.deployed.prefab")] = XR("Large Battery");
		ObjectsNames[XR("assets/prefabs/deployable/playerioents/batteries/medium/medium.rechargable.battery.deployed.prefab")] = XR("Medium Battery");
		ObjectsNames[XR("assets/prefabs/deployable/playerioents/batteries/smallrechargablebattery.deployed.prefab")] = XR("Small Battery");

/*
		ObjectsNames[XR("core/foundation/foundation.prefabassets/prefabs/building")] = XR("Foundation");
		ObjectsNames[XR("assets/prefabs/building core/foundation/foundation.prefab")] = XR("Foundation");
*/
		//ObjectsNames[XR("")] = XR("");

		alf = true;
	}
}