#include "Miscellaneous.h"
#include "imgui/imgui.h"
#include <m_includes/XorStr/XR.hpp>
#include "rust.h"
#include "global.h"
#include "Hotkey.h"
namespace Miscellaneous
{
	namespace config
	{
		//bool killlocalplayer = false;
		bool spiderman = false;
		bool infinite_jump = false;
		bool long_melee = false;
		bool removelayers = false;
		HotKeys* killlocalplayer = new HotKeys();
		std::vector<std::shared_ptr<BasePlayer>> Onlines() {
			std::vector<std::shared_ptr<BasePlayer>> results{};
			rust::BaseLocalPlayer->InitializePlayerList();
			rust::BaseLocalPlayer->CachePlayers();

			for (std::shared_ptr<BasePlayer> player : rust::BaseLocalPlayer->GetPlayerList())
			{
				if (!player->IsPlayerValid())
					continue;

				if (player->GetClass() == rust::BaseLocalPlayer->GetClass())
					continue;

				player->UpdateDestroyed();
				player->UpdateActiveFlag();

				if (player->IsDead())
					continue;

				if (player->IsNPC())
					continue;

				results.push_back(player);

			}
			return results;
		}

	}
	void Miscellaneous::Render() {

		if (ImGui::BeginTabBar(XR("entity")))
		{
			if (ImGui::BeginTabItem(XR("Self")))
			{
				ImGui::Checkbox(XR("Kill localplayer"), &config::killlocalplayer->toggel);
				ImGui::SameLine();
				GUI::HotKey(config::killlocalplayer, ImVec2(23, 23));
				ImGui::Checkbox(XR("Spiderman"), &config::spiderman);
				ImGui::Checkbox(XR("Infinite jump"), &config::infinite_jump);
				//ImGui::Checkbox(XR("Remove layers"), &config::removelayers);
				//ImGui::Checkbox(XR("Long Melee"), &config::long_melee);
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(XR("Online Players")))
			{
					if (ImGui::BeginListBox(XR("Online Players"), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y)))
					{
						for (auto& player : config::Onlines())
						{
							std::string player_name = player->GetNameS();

							// Ensure the player class is initialized if not present
							if (global::PlayerClasses.find(player_name) == global::PlayerClasses.end())
							{
								global::PlayerClasses[player_name] = global::PlayerClass::player;
							}

							// Append the player class to the player name
							std::string display_name = player_name;
							switch (global::PlayerClasses[player_name])
							{
							case global::PlayerClass::friends:
								display_name.append(XR(" Friend"));
								break;
							case global::PlayerClass::player:
								display_name.append(XR(" Player"));
								break;
							case global::PlayerClass::enemy:
								display_name.append(XR(" Enemy"));
								break;
							case global::PlayerClass::cheater:
								display_name.append(XR(" Cheater"));
								break;
							}

							ImGui::Text(display_name.c_str());

							// Handle item click to cycle through player classes
							if (ImGui::IsItemClicked())
							{
								global::PlayerClasses[player_name] = static_cast<global::PlayerClass>((global::PlayerClasses[player_name] + 1) % 4);
							}
						}
						ImGui::EndListBox();
					}
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		//ImGui::Checkbox(XR("Long Melle"), &config::long_melee);
	}
	void Miscellaneous::Threads() {

/*
		if (config::long_melee)
		{
			rust::BaseLocalPlayer->SetupBeltContainerList();
			rust::BaseLocalPlayer->UpdateActiveItemID();
			rust::BaseLocalPlayer->UpdateActiveFlag();
			std::shared_ptr <Item> helditem = rust::BaseLocalPlayer->GetActiveItem();
			if (helditem != nullptr)
			{
				std::shared_ptr <BaseProjectile> weapon = helditem->GetBaseProjectile();
				if (weapon != 0)
				{
					weapon->WriteSpread
				}
			}
		}
*/

		if (config::removelayers)
		{
/*
			for (int i = 0; i < 1000000; i++)
			{
				rust::Sky->WriteCullingMaskLayers(i);
				std::cout << "Mask : " << i << std::endl;
				Sleep(300);
			}
			config::removelayers = false;
*/
			rust::OcclusionCullingC->WriteLayerMask(0);
			rust::OcclusionCullingC->WriteDebugSettings(DebugFilter::Off);
		}

		if (config::infinite_jump)
		{
			rust::BaseLocalPlayer->GetBaseMovement()->WriteJumpTime(0.f);
			auto GroundTime = rust::BaseLocalPlayer->GetBaseMovement()->GetGroundTime() + 0.5f;
			rust::BaseLocalPlayer->GetBaseMovement()->WriteGroundTime(GroundTime);
			rust::BaseLocalPlayer->GetBaseMovement()->WriteLandTime(0.f);
		}
		if (config::spiderman)
		{
			rust::BaseLocalPlayer->GetBaseMovement()->WriteGroundAngleNew(0.f);
		}
		if (config::killlocalplayer->toggel)
		{
			if (config::killlocalplayer->key != 0)
			{
				if (GetAsyncKeyState(config::killlocalplayer->key) & 0x8000)
				{
					rust::BaseLocalPlayer->GetBaseMovement()->WasFalling(true);
					rust::BaseLocalPlayer->GetBaseMovement()->SetPreviousVelocity(Vector3(0, -20, 0));
					rust::BaseLocalPlayer->GetBaseMovement()->WriteGroundTime(0.f);
				}
			}
		}
		if (config::long_melee)
		{
			rust::BaseLocalPlayer->SetupBeltContainerList();
			rust::BaseLocalPlayer->UpdateActiveItemID();
			rust::BaseLocalPlayer->UpdateActiveFlag();
			std::shared_ptr<Item> helditem = rust::BaseLocalPlayer->GetActiveItem();
			if (helditem != nullptr)
			{
				std::shared_ptr<BaseProjectile> weapon = helditem->GetBaseProjectile();
				if (weapon != nullptr)
				{
					weapon->LongHand(helditem->GetItemID());
				}
			}
		}
	}
}