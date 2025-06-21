#include "Visuals.h"
#include <m_includes/XorStr/XR.hpp>
#include "imgui/imgui.h"
#include "rust.h"
#include "global.h"
namespace function
{
	void DrawBorder(ImDrawList* draw_list, const ImVec2& pos_a, const ImVec2& pos_b, ImColor col, float rounding/*=0.0f*/, int rounding_corners /*=-1*/, float thickness)
	{
		draw_list->AddRect(pos_a, { pos_a.x + pos_b.x, pos_a.y + pos_b.y }, col, 0.0f, rounding_corners, thickness);
	}
	ImVec2 VecI2(Vector2 vec)
	{
		return ImVec2(vec.x, vec.y);
	}
}

namespace Visuals
{
	namespace config
	{
		ImVec2 WindowSize = ImVec2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
		bool enable = false;
		bool box = false;
		bool snaplines = false;
		bool name = false;
		bool Distance = false;
		bool npcs = false;
		bool weapon = false;
		bool show_sleaping = false;
		bool Skeleton = false;
		float MaxDistance = 400;
		bool headbox = false;

		///colors
		inline ImColor box_color(255, 255, 255, 255);
		inline ImColor Friend_color(0, 252, 29, 255);
		inline ImColor snaplines_color(255, 255, 255, 255);
		inline ImColor skeleton_color(255, 255, 255, 255);

		inline float box_f[4] = { 255.f, 242.f, 0.f, 200.f };
		inline float skeleton_f[4] = { 255.f, 242.f, 0.f, 200.f };
		inline float snaplines_f[4] = { 255.f, 242.f, 0.f, 200.f };
		inline float Friend_f[4] = { 0.0f, 0.988f, 0.114f, 0.784f };

	}

	void Visuals::Render()
	{
		ImGui::BeginChild(XR("##esp_1"), ImVec2(ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y));
		{
			ImGui::Checkbox(XR("Enable"), &config::enable);
			ImGui::Checkbox(XR("Box"), &config::box);
			ImGui::SameLine();
			ImGui::Checkbox(XR("Snaplines"), &config::snaplines);
			ImGui::Checkbox(XR("Skeleton"), &config::Skeleton);
			ImGui::SameLine();
			ImGui::Checkbox(XR("Sleeping"), &config::show_sleaping);
			ImGui::Checkbox(XR("Name"), &config::name);
			ImGui::SameLine();
			ImGui::Checkbox(XR("Distance"), &config::Distance);
			ImGui::Checkbox(XR("Weapon"), &config::weapon);
			ImGui::SameLine();
			ImGui::Checkbox(XR("Show NPC"), &config::npcs);
			ImGui::Checkbox(XR("Head Box"), &config::headbox);
		}
		ImGui::EndChild();
		ImGui::SameLine();
		ImGui::BeginChild(XR("##esp_2"), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));
		{
			ImGui::Text(XR("Box Color"));
			ImGui::SameLine();
			ImGui::ColorEdit4(((XR("##box"))), config::box_f, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
			config::box_color.Value.x = config::box_f[0];
			config::box_color.Value.y = config::box_f[1];
			config::box_color.Value.z = config::box_f[2];
			config::box_color.Value.w = config::box_f[3];

			ImGui::Text(XR("Skeleton Color"));
			ImGui::SameLine();
			ImGui::ColorEdit4(((XR("##skssss"))), config::skeleton_f, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
			config::skeleton_color.Value.x = config::skeleton_f[0];
			config::skeleton_color.Value.y = config::skeleton_f[1];
			config::skeleton_color.Value.z = config::skeleton_f[2];
			config::skeleton_color.Value.w = config::skeleton_f[3];


			ImGui::Text(XR("SnapLine Color"));
			ImGui::SameLine();
			ImGui::ColorEdit4((XR("##snapline")), config::snaplines_f, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
			config::snaplines_color.Value.x = config::snaplines_f[0];
			config::snaplines_color.Value.y = config::snaplines_f[1];
			config::snaplines_color.Value.z = config::snaplines_f[2];
			config::snaplines_color.Value.w = config::snaplines_f[3];

			ImGui::Text(XR("Friend Color"));
			ImGui::SameLine();
			ImGui::ColorEdit4(((XR("##Friendcolor"))), config::Friend_f, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
			config::Friend_color.Value.x = config::Friend_f[0];
			config::Friend_color.Value.y = config::Friend_f[1];
			config::Friend_color.Value.z = config::Friend_f[2];
			config::Friend_color.Value.w = config::Friend_f[3];
			ImGui::SliderFloat(XR("MaxDistance"), &config::MaxDistance, 0, 400);
		}
		ImGui::EndChild();
	}
	void Visuals::Thread()
	{
		if (config::enable && rust::BaseLocalPlayer)
		{
			//rust::BaseNetworkableC->ItterateEntities();
			if (rust::BaseLocalPlayer->IsPlayerValid())
			{
				rust::BaseLocalPlayer->InitializePlayerList();
				rust::BaseLocalPlayer->CachePlayers();

				for (std::shared_ptr<BasePlayer> player : rust::BaseLocalPlayer->GetPlayerList())
				{
					std::string str;

					bool is_class = false;
					ImColor override_color = ImColor(255, 255, 255, 255);
					if (global::PlayerClasses.find(player->GetNameS()) != global::PlayerClasses.end())
					{
						switch (global::PlayerClasses[player->GetNameS()])
						{
						case global::PlayerClass::friends:
							is_class = true;
							override_color = ImColor(0, 252, 29, 255);
							break;
						case global::PlayerClass::player:
							is_class = false;
							break;
						case global::PlayerClass::enemy:
							is_class = true;
							override_color = ImColor(255, 94, 0);
							break;
						case global::PlayerClass::cheater:
							is_class = true;
							override_color = ImColor(255, 0, 0);
							break;
						}
					}


					if (!player->IsPlayerValid())
						continue;
					if (player->GetClass() == rust::BaseLocalPlayer->GetClass())
						continue;
					player->UpdatePosition();
					player->UpdateDestroyed();
					player->UpdateActiveFlag();
					if (!config::show_sleaping)
					{
						if (player->IsSleeping())
							continue;
					}

					if (player->IsDead())
						continue;

					if (!config::npcs)
					{
						if (player->IsNPC())
							continue;
					}
					player->UpdatePosition();
					player->UpdateDestroyed();
					player->UpdateActiveFlag();
					//printf("a player was found\n");

					Vector3 position = player->GetPosition();
					if (position == Vector3(0, 0, 0))
					{
						continue;
					}

					Vector2 screenpos = rust::WorldToScreen(position);
					if (screenpos.x == 0 && screenpos.y == 0)
					{
						continue;
					}
					rust::BaseLocalPlayer->UpdatePosition();
					int distance = (int)Vector3::Distance(position, rust::BaseLocalPlayer->GetPosition());
					if (distance > config::MaxDistance)
						continue;


					if (config::Skeleton)
					{
						auto head = player->GetBonePosition(BoneList::head);
						auto _neck = player->GetBonePosition(BoneList::neck);
						auto spine = player->GetBonePosition(BoneList::spine1);
						auto lupper = player->GetBonePosition(BoneList::l_upperarm);
						auto rupper = player->GetBonePosition(BoneList::r_upperarm);
						auto lfore = player->GetBonePosition(BoneList::l_forearm);
						auto rfore = player->GetBonePosition(BoneList::r_forearm);
						auto lhand = player->GetBonePosition(BoneList::l_hand);
						auto rhand = player->GetBonePosition(BoneList::r_hand);
						auto lknee = player->GetBonePosition(BoneList::l_knee);
						auto rknee = player->GetBonePosition(BoneList::r_knee);
						auto lhip = player->GetBonePosition(BoneList::l_hip);
						auto rhip = player->GetBonePosition(BoneList::r_hip);
						auto right_foot = player->GetBonePosition(BoneList::r_foot);
						auto left_foot = player->GetBonePosition(BoneList::l_foot);

						Vector2 chest, l_foot, r_foot, _head, l_shoulder, r_shoulder, l_forearm, r_forearm, l_hand, r_hand, neck, l_arm, r_arm, l_knee, r_knee, l_hipbone, r_hipbone;
						if (!rust::WorldToScreen2(head, _head, false))
							continue;
						if (!rust::WorldToScreen2(_neck, neck, false))
							continue;
						if (!rust::WorldToScreen2(spine, chest, false))
							continue;
						if (!rust::WorldToScreen2(lupper, l_shoulder, false))
							continue;
						if (!rust::WorldToScreen2(rupper, r_shoulder, false))
							continue;
						if (!rust::WorldToScreen2(lfore, l_forearm, false))
							continue;
						if (!rust::WorldToScreen2(rfore, r_forearm, false))
							continue;
						if (!rust::WorldToScreen2(lhand, l_hand, false))
							continue;
						if (!rust::WorldToScreen2(rhand, r_hand, false))
							continue;
						if (!rust::WorldToScreen2(lknee, l_knee, false))
							continue;
						if (!rust::WorldToScreen2(rknee, r_knee, false))
							continue;
						if (!rust::WorldToScreen2(lhip, l_hipbone, false))
							continue;
						if (!rust::WorldToScreen2(rhip, r_hipbone, false))
							continue;
						if (!rust::WorldToScreen2(left_foot, l_foot, false))
							continue;
						if (!rust::WorldToScreen2(right_foot, r_foot, false))
							continue;

						auto draw = ImGui::GetBackgroundDrawList();

						if (is_class)
						{
							draw->AddLine(function::VecI2(_head), function::VecI2(neck), override_color);
							draw->AddLine(function::VecI2(neck), function::VecI2(chest), override_color);

							draw->AddLine(function::VecI2(neck), function::VecI2(l_shoulder), override_color);
							draw->AddLine(function::VecI2(l_shoulder), function::VecI2(l_forearm), override_color);
							draw->AddLine(function::VecI2(l_forearm), function::VecI2(l_hand), override_color);

							draw->AddLine(function::VecI2(chest), function::VecI2(l_hipbone), override_color);
							draw->AddLine(function::VecI2(l_hipbone), function::VecI2(l_knee), override_color);
							draw->AddLine(function::VecI2(l_knee), function::VecI2(l_foot), override_color);


							draw->AddLine(function::VecI2(neck), function::VecI2(r_shoulder), override_color);
							draw->AddLine(function::VecI2(r_shoulder), function::VecI2(r_forearm), override_color);
							draw->AddLine(function::VecI2(r_forearm), function::VecI2(r_hand), override_color);

							draw->AddLine(function::VecI2(chest), function::VecI2(r_hipbone), override_color);
							draw->AddLine(function::VecI2(r_hipbone), function::VecI2(r_knee), override_color);
							draw->AddLine(function::VecI2(r_knee), function::VecI2(r_foot), override_color);
						}
						else
						{
							draw->AddLine(function::VecI2(_head), function::VecI2(neck), config::skeleton_color);
							draw->AddLine(function::VecI2(neck), function::VecI2(chest), config::skeleton_color);

							draw->AddLine(function::VecI2(neck), function::VecI2(l_shoulder), config::skeleton_color);
							draw->AddLine(function::VecI2(l_shoulder), function::VecI2(l_forearm), config::skeleton_color);
							draw->AddLine(function::VecI2(l_forearm), function::VecI2(l_hand), config::skeleton_color);

							draw->AddLine(function::VecI2(chest), function::VecI2(l_hipbone), config::skeleton_color);
							draw->AddLine(function::VecI2(l_hipbone), function::VecI2(l_knee), config::skeleton_color);
							draw->AddLine(function::VecI2(l_knee), function::VecI2(l_foot), config::skeleton_color);


							draw->AddLine(function::VecI2(neck), function::VecI2(r_shoulder), config::skeleton_color);
							draw->AddLine(function::VecI2(r_shoulder), function::VecI2(r_forearm), config::skeleton_color);
							draw->AddLine(function::VecI2(r_forearm), function::VecI2(r_hand), config::skeleton_color);

							draw->AddLine(function::VecI2(chest), function::VecI2(r_hipbone), config::skeleton_color);
							draw->AddLine(function::VecI2(r_hipbone), function::VecI2(r_knee), config::skeleton_color);
							draw->AddLine(function::VecI2(r_knee), function::VecI2(r_foot), config::skeleton_color);
						}
					}

					if (config::snaplines)
					{
						auto draw = ImGui::GetBackgroundDrawList();
						ImVec2 other_player = ImVec2(screenpos.x, screenpos.y);
						if (is_class)
						{
							draw->AddLine(ImVec2(config::WindowSize.x / 2, config::WindowSize.y), other_player, override_color, 1.0f);
						}
						else
						{
							draw->AddLine(ImVec2(config::WindowSize.x / 2, config::WindowSize.y), other_player, config::snaplines_color, 1.0f);
						}
					}

					if (config::name)
					{
						str.append(player->GetNameS()).append(XR(" "));
						if (global::PlayerClasses.find(player->GetNameS()) != global::PlayerClasses.end())
						{
							switch (global::PlayerClasses[player->GetNameS()])
							{
							case global::PlayerClass::friends:
								str.append(XR(" Friend "));
								break;
							case global::PlayerClass::player:
								is_class = false;
								break;
							case global::PlayerClass::enemy:
								str.append(XR(" Enemy "));
								break;
							case global::PlayerClass::cheater:
								str.append(XR(" Cheater "));
								break;
							}
						}
					}

					if (config::Distance)
					{
						str.append(XR(" [")).append(std::to_string(distance)).append(XR("]m"));
					}

					if (config::weapon)
					{
						player->SetupBeltContainerList();
						player->UpdateActiveItemID();
						player->UpdateActiveFlag();
						std::shared_ptr <Item> helditem = player->GetActiveItem();
						if (helditem != nullptr)
						{
							std::string weapon_name = helditem->GetItemDisplayName(helditem->GetItemName());

							str.append(XR("\n") + weapon_name).append(XR(" "));
						}
					}

					if (config::box)
					{
						Vector2 tempFeet = screenpos;
						Vector3 tempHeadPos = Vector3(position) + Vector3(0, 1.7, 0);
						Vector2 tempHead = rust::WorldToScreen(tempHeadPos);
						float h = tempHead.y - tempFeet.y;
						float w = h / 4;

						if (is_class)
						{
							function::DrawBorder(ImGui::GetBackgroundDrawList(), ImVec2((int)tempFeet.x - w, (int)tempFeet.y), ImVec2((int)w * 2, (int)h), override_color, 0, -1, 1.5);
						}
						else
						{
							function::DrawBorder(ImGui::GetBackgroundDrawList(), ImVec2((int)tempFeet.x - w, (int)tempFeet.y), ImVec2((int)w * 2, (int)h), config::box_color, 0, -1, 1.5);
						}


					}

					if (config::name || config::Distance || config::weapon)
					{
						auto draw = ImGui::GetBackgroundDrawList();

						auto size = ImGui::CalcTextSize(str.c_str());
						ImVec2 other_player = ImVec2(screenpos.x - 63, screenpos.y);
						draw->AddText(other_player, ImColor(255, 255, 255), str.c_str());
					}
				}

			}
		}
	}
}