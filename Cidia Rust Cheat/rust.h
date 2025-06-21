#pragma once
#include "global.h"
#include <m_includes/XorStr/XR.hpp>
#include "MainCamera.h"
#include "ConvarGraphics.h"
#include "ConvarAdmin.h"
#include "ConsoleSystem.h"
#include "LocalPlayer.h"
#include "BaseNetworkable.h"
#include "BasePlayer.h"
#include "TODSky.h"
#include "CheatFunction.h"
#include "OcclusionCulling.h"
#include <Windows.h>
#include "ConvarGraphics.h"
#include "GameObjectManager.h"
#include "Projectile.h"
namespace rust
{
	inline bool o = false;
	inline std::shared_ptr<BasePlayer> BaseLocalPlayer = nullptr;
	inline std::shared_ptr<MainCamera> Camera = nullptr;
	inline std::shared_ptr<ConsoleSystem> Console = nullptr;
	inline std::shared_ptr<TODSky> Sky = nullptr;
	inline std::shared_ptr<BaseNetworkable> BaseNetworkableC = nullptr;
    inline std::shared_ptr<ConvarGraphics> ConvarGraphicsC = nullptr;
    inline std::shared_ptr<OcclusionCulling> OcclusionCullingC = nullptr;
    inline GameObjectManager* GameObjectManagerC = new GameObjectManager();
    inline int cts = 0;
    inline bool b = false;
    inline void PerServerVariables()
    {

        if (!b)
        {
            BaseNetworkableC = std::make_shared<BaseNetworkable>();
            std::shared_ptr <LocalPlayer> localplayer = std::make_shared <LocalPlayer>();
            BaseLocalPlayer = std::make_shared <BasePlayer>(localplayer->GetBasePlayer());
            BaseLocalPlayer->InitializePlayerList();
            BaseLocalPlayer->CacheStage1();
            Camera = std::make_shared <MainCamera>();
            ConvarGraphicsC = std::make_shared <ConvarGraphics>();
            Sky = std::make_shared<TODSky>();
            OcclusionCullingC = std::make_shared<OcclusionCulling>();
            b = true;
        }


/*
        cts++;
        if (cts >= 2000)
        {
            std::string cmd = XR("cls");
            const char* command = cmd.c_str();
            system(command);
            BaseNetworkableC = std::make_shared<BaseNetworkable>();
            std::shared_ptr <LocalPlayer> localplayer = std::make_shared <LocalPlayer>();
            BaseLocalPlayer = std::make_shared <BasePlayer>(localplayer->GetBasePlayer());
            BaseLocalPlayer->InitializePlayerList();
            BaseLocalPlayer->CacheStage1();
            Camera = std::make_shared <MainCamera>();
            ConvarGraphicsC = std::make_shared <ConvarGraphics>();
            Sky = std::make_shared<TODSky>();
            OcclusionCullingC = std::make_shared<OcclusionCulling>();
            global::print(XR("Re-loaded"));
            cts = 0;
        }
*/

    }

	inline ViewMatrix CurrentMatrix;

	inline Vector2 WorldToScreen(const Vector3& position)
	{
        CurrentMatrix = Camera->GetViewMatrix();
		Vector3 transform(CurrentMatrix.matrix[0][3], CurrentMatrix.matrix[1][3], CurrentMatrix.matrix[2][3]);
		Vector3 right(CurrentMatrix.matrix[0][0], CurrentMatrix.matrix[1][0], CurrentMatrix.matrix[2][0]);
		Vector3 up(CurrentMatrix.matrix[0][1], CurrentMatrix.matrix[1][1], CurrentMatrix.matrix[2][1]);

		float w = Vector3::Dot(transform, position) + CurrentMatrix.matrix[3][3];

		if (w < 1.f)
			return Vector2(0, 0);
		float x = Vector3::Dot(right, position) + CurrentMatrix.matrix[3][0];
		float y = Vector3::Dot(up, position) + CurrentMatrix.matrix[3][1];

		return  Vector2((GetSystemMetrics(SM_CXSCREEN) / 2) * (1.f + x / w), (GetSystemMetrics(SM_CYSCREEN) / 2) * (1.f - y / w)); // grab screen.width and height later.
	}

	inline bool WorldToScreen2(const Vector3& element_position, Vector2& screen_position, bool ignore_incorrect)
	{
		// Null check for element_position
		if (&element_position == nullptr)
		{
			// Handle the error, log it, or return false
			return false;
		}

		if (element_position.x == 0 || element_position.y == 0 || element_position.z == 0)
		{
			return false;
		}

		CurrentMatrix = Camera->GetViewMatrix();
		Vector3 trans_vec(CurrentMatrix.matrix[0][3], CurrentMatrix.matrix[1][3], CurrentMatrix.matrix[2][3]);
		Vector3 right_vec(CurrentMatrix.matrix[0][0], CurrentMatrix.matrix[1][0], CurrentMatrix.matrix[2][0]);
		Vector3 up_vec(CurrentMatrix.matrix[0][1], CurrentMatrix.matrix[1][1], CurrentMatrix.matrix[2][1]);

		const float w = Vector3::Dot(trans_vec, element_position) + CurrentMatrix.matrix[3][3];
		bool bad = false;


		if (w < 1.f)
		{
			if (!ignore_incorrect)
				return false;
			else
				bad = true;
		}


		float x = Vector3::Dot(right_vec, element_position) + CurrentMatrix.matrix[3][0];
		float y = Vector3::Dot(up_vec, element_position) + CurrentMatrix.matrix[3][1];

		Vector2 screen_pos = { (GetSystemMetrics(SM_CXSCREEN) / 2) * (1.f + x / w), (GetSystemMetrics(SM_CYSCREEN) / 2) * (1.f - y / w) };
		screen_position = screen_pos;

		if (screen_pos.x >= GetSystemMetrics(SM_CXSCREEN) || screen_pos.y >= GetSystemMetrics(SM_CYSCREEN) || screen_pos.x <= 0 || screen_pos.y <= 0 || bad)
			return false;

		return true;
	}

    inline bool getItemName(uint64_t code, std::string* out) {
        // Create a mapping of codes to item names
        static const std::unordered_map<uint64_t, std::string> codeToName = {
            {962510733, "ICE AK"},
            {1288283338, "NORMAL AK"},
            {3123209028, "ABYSS AK"},
            {2175953388, "Butcher knife"},
            {2422338964, "Bolt action"},
            {962510733, "Combat knife"},
            {962510733, "Compound bow"},
            {2105161176, "Crossbow"},
            {1855311151, "Custom SMG"},
            {3123209028, "Double barrel shotgun"},
            {4052064619, "Rocket launcher"},
            {3556394590, "Eoka Pistol"},
            {3230621985, "Hmlmg"},
            {663976840, "Homing Missile launcher"},
            {3556394590, "L96 Rifle"},
            {3230621985, "Hunting Bow"},
            {1855311151, "M249"},
            {1288283338, "Longsword"},
            {2422338964, "LR-300 Rifle"},
            {1855311151, "M39"},
            {1855311151, "M4 Shotgun"},
            {3556394590, "Lunar new year spear"},
            {3755895493, "Machete"},
            {2744923934, "Military Flame Thrower"},
            {1855311151, "Minigun"},
            {3082256702, "Molotov"},
            {3230621985, "M92 Pistol"},
            {1849821077, "Mace"},
            {2175953388, "Python Revolver"},
            {1009987116, "Prototype 17"},
            {962510733, "Pump Shotgun"},
            {3123209028, "Nailgun"},
            {3755895493, "MP5A4"},
            {1326826969, "Multiple Grenade Launcher"},
            {3755895493, "Thompson"},
            {3691348435, "Revolver"},
            {570490775, "Rocket Launcher"},
            {4086325918, "Semi-Automatic Pistol"},
            {3123209028, "Semi-Automatic Rifle"},
            {3556394590, "SKS"},
            {3123209028, "Spas-12 Shotgun"},
            {1288283338, "Speargun"},
            {3820980142, "Waterpipe Shotgun"},
            {3556394590, "Pistol Bullet"},
            {1844507683, "Incendiary Pistol Bullet"},
            {3123209028, "HV Pistol Ammo"},
            {3556394590, "5.56 Rifle Ammo"},
            {1168459013, "Incendiary 5.56 Rifle Ammo"},
            {2175953388, "HV 5.56 Rifle Ammo"},
            {1464486169, "Explosive 5.56 Rifle Ammo"},
            {962510733, "12 Gauge Buckshot"},
            {1857313597, "12 Gauge Incendiary Shell"},
            {4108881093, "12 Gauge Slug"},
            {3365200198, "Handmade Shell"},
            {339222755, "Nailgun Nails"},
            {962510733, "Wooden Arrow"},
            {3230621985, "High Velocity Arrow"},
            {3755895493, "Bone Arrow"},
            {3230621985, "Fire Arrow"},
            {1663554342, "Rocket"},
            {2797867453, "Incendiary Rocket"},
            {3123209028, "High Velocity Rocket"},
            {339222755, "Homing Missile"},
            {1260996869, "Smoke Rocket"},
            {1487744138, "Mlrs Rocket"},
            {2453689165, "SAM Ammo"},
            {1203964042, "Torpedo"},
            {1689045669, "HOT SPOT"},
            {147189280, "Sulfur Ore"},
            {3159193003, "Metal Ore"},
            {2114314665, "Stone Ore"},
            {2067050770, "TC"},
            {1388820292, "Loot Crates"},
            {1413032903, "Loot Barrel"},
            {387973387, "Loot Barrel"},
            {1966426602, "Loot Barrel"},
            {3531127234, "Loot Barrel"},
            {51176339, "Loot Barrel"},
            {1442764608, "Loot Barrel"},
            {2437105454, "Military crate"}
        };

        // Find the code in the map and return the corresponding name
        auto it = codeToName.find(code);
        if (it != codeToName.end()) {
            *out = it->second;
            return true;
        }
        else {
            return false;
        }
    }

}