#include "EntityESP.h"
#include "imgui/imgui.h"
#include <m_includes/XorStr/XR.hpp>
#include "rust.h"
//#include "fnv1a.hpp"
#include "Driver.h"
#include <string>
#include <strstream>
#include <sstream>
#include "hash.h"

namespace EntityESP
{

	namespace raid
	{
		bool enable = false;
		bool showdistance = false;
		bool raid_esp = false;
		bool raid_home_esp = false;
		bool hide_base_objects = false;
		Vector3 home_base = Vector3(0,0,0);
	}

	class TraceVector
	{
	public:
	//	std::vector<Vector2> trace;
		ImColor color = ImColor(255,255,255,255);
		int time = 0;
		Vector3 pos;
		std::string string;
		bool raid = false;
		bool dis = false;
	};

	std::map<uintptr_t, TraceVector*> TraceVectorImpl;

	void RenderObject(std::string string, int distance, Vector3 pos, bool namespaceT, ImDrawList* draw, ImColor color = ImColor(255,255,255))
	{
		std::string str = string;
		if (namespaceT)
		{
			str.append(XR(" [")).append(std::to_string(distance)).append(XR("]m"));
		}

		if (raid::hide_base_objects)
		{
			if (raid::home_base.x != 0 && raid::home_base.y != 0 && raid::home_base.z != 0)
			{
				rust::BaseLocalPlayer->UpdatePosition();
				int distance = (int)Vector3::Distance(pos, raid::home_base);

				if (distance > 25)
				{
					auto size = ImGui::CalcTextSize(str.c_str());
					auto screenpos = rust::WorldToScreen(pos);


					if (screenpos.x != 0)
					{
						if (screenpos.y != 0)
						{
							ImVec2 other_player(screenpos.x, screenpos.y);

							draw->AddText(other_player, color, str.c_str());
						}
					}
				}
				else
				{
					//do nothing :D
				}

			}
		}
		else
		{
			auto size = ImGui::CalcTextSize(str.c_str());
			auto screenpos = rust::WorldToScreen(pos);


			if (screenpos.x != 0)
			{
				if (screenpos.y != 0)
				{
					ImVec2 other_player(screenpos.x, screenpos.y);

					draw->AddText(other_player, color, str.c_str());
				}
			}
		}


		/*
		ImVec2 other_player(screenpos.x, screenpos.y);

		draw->AddText(other_player, ImColor(255, 255, 255), str.c_str());
		*/
	}

	void RenderRaidHomeObject(std::string string, int distance, Vector3 pos, bool namespaceT, Vector3 home_pos, ImDrawList* draw, uintptr_t cls)
	{

		if (home_pos.x != 0 && home_pos.y != 0) {
			int calculatedDistance = static_cast<int>(Vector3::Distance(pos, home_pos));


			if (calculatedDistance < 35) {
				std::string str = XR("RAID AT HOME | ") + string;
				std::cout << str << std::endl;
				/*
				if (namespaceT) {
					str.append(XR(" [")).append(std::to_string(calculatedDistance)).append(XR("]m"));
				}
				*/

				if (TraceVectorImpl.find(cls) == TraceVectorImpl.end()) {
					TraceVector* trace = new TraceVector();
					trace->color = ImColor(255, 0, 0);
					trace->pos = pos;
					trace->raid = true;
					trace->dis = namespaceT;
					trace->string = str;
					TraceVectorImpl[cls] = trace;
				}
				else {
					TraceVectorImpl[cls]->pos = pos;
					TraceVectorImpl[cls]->color = ImColor(255, 0, 0);
					TraceVectorImpl[cls]->string = str; // Update string if necessary
				}
			}
		}
	}

	void RenderRaidObject(std::string string, int distance, Vector3 pos, bool namespaceT, ImDrawList* draw, uintptr_t cls)
	{
		std::string str = XR("RAID | ") + string;
/*
		if (namespaceT)
		{
			str.append(XR(" [")).append(std::to_string(distance)).append(XR("]m"));
		}
*/

		if (raid::hide_base_objects)
		{
			if (raid::home_base.x != 0 && raid::home_base.y != 0 && raid::home_base.z != 0)
			{
				rust::BaseLocalPlayer->UpdatePosition();
				int distance = (int)Vector3::Distance(pos, raid::home_base);

				if (distance > 25)
				{
					if (TraceVectorImpl.find(cls) == TraceVectorImpl.end())
					{
						TraceVector* trace = new TraceVector();
						trace->color = ImColor(252, 186, 3);
						trace->pos = pos;
						trace->raid = true;
						trace->dis = namespaceT;
						trace->string = str;
						TraceVectorImpl[cls] = trace;
					}
					else
					{
						TraceVectorImpl[cls]->pos = pos;
						//TraceVectorImpl[cls]->color = ImColor(252, 186, 3);
						//TraceVectorImpl[cls]->string = str; // Update string if necessary
					}
				}
				else
				{
					//do nothing :D
				}

			}
		}
		else
		{
			if (TraceVectorImpl.find(cls) == TraceVectorImpl.end())
			{
				TraceVector* trace = new TraceVector();
				trace->color = ImColor(252, 186, 3);
				trace->pos = pos;
				trace->raid = true;
				trace->dis = namespaceT;
				trace->string = str;
				TraceVectorImpl[cls] = trace;
			}
			else
			{
				TraceVectorImpl[cls]->pos = pos;
				//TraceVectorImpl[cls]->color = ImColor(252, 186, 3);
				//TraceVectorImpl[cls]->string = str; // Update string if necessary
			}
		}
		/*
		auto size = ImGui::CalcTextSize(str.c_str());
		auto screenpos = rust::WorldToScreen(pos);


		if (screenpos.x != 0)
		{
			if (screenpos.y != 0)
			{
				ImVec2 other_player(screenpos.x, screenpos.y);

				draw->AddText(other_player, ImColor(252, 186, 3), str.c_str());
			}
		}
		*/
	}

	void RenderObjectWithTrace(std::string string, int distance, Vector3 pos, bool namespaceT, ImDrawList* draw, bool trace, uintptr_t calss)
	{
		std::string str = string;
		if (namespaceT)
		{
			str.append(XR(" [")).append(std::to_string(distance)).append(XR("]m"));
		}

		if (raid::hide_base_objects)
		{
			if (raid::home_base.x != 0 && raid::home_base.y != 0 && raid::home_base.z != 0)
			{
				rust::BaseLocalPlayer->UpdatePosition();
				int distance = (int)Vector3::Distance(pos, raid::home_base);

				if (distance > 25)
				{
					auto size = ImGui::CalcTextSize(str.c_str());
					auto screenpos = rust::WorldToScreen(pos);

					if (trace)
					{
						if (TraceVectorImpl.find(calss) == TraceVectorImpl.end())
						{
							TraceVector* Trace = new TraceVector();
							TraceVectorImpl[calss] = Trace;
						}
						else
						{
							TraceVectorImpl[calss]->pos = pos;
						}
					}

					if (screenpos.x != 0)
					{
						if (screenpos.y != 0)
						{
							ImVec2 other_player(screenpos.x, screenpos.y);

							draw->AddText(other_player, ImColor(255, 255, 255), str.c_str());
						}
					}
				}
				else
				{
					//do nothing :D
				}

			}
		}
		else
		{
			auto size = ImGui::CalcTextSize(str.c_str());
			auto screenpos = rust::WorldToScreen(pos);

			if (trace)
			{
				if (TraceVectorImpl.find(calss) == TraceVectorImpl.end())
				{
					TraceVector* Trace = new TraceVector();
					TraceVectorImpl[calss] = Trace;
				}
				else
				{
					TraceVectorImpl[calss]->pos = pos;
				}
			}

			if (screenpos.x != 0)
			{
				if (screenpos.y != 0)
				{
					ImVec2 other_player(screenpos.x, screenpos.y);

					draw->AddText(other_player, ImColor(255, 255, 255), str.c_str());
				}
			}
		}
	}

	void RaidThread() {
		if (TraceVectorImpl.size() >= 1)
		{
			for (auto& trace : TraceVectorImpl)
			{
				if (trace.second->raid)
				{
					trace.second->time++;
					if (trace.second->time >= 1500)
					{
						TraceVectorImpl.erase(trace.first);
					}
					else
					{
						auto draw = ImGui::GetBackgroundDrawList();
						std::string str = trace.second->string;
						if (trace.second->dis)
						{
							rust::BaseLocalPlayer->UpdatePosition();
							int distance = (int)Vector3::Distance(trace.second->pos, rust::BaseLocalPlayer->GetPosition());
							str.append( XR(" [")).append( std::to_string(distance) ).append(XR("]m") );
						}

						auto size = ImGui::CalcTextSize( str.c_str() );
						auto screenpos = rust::WorldToScreen( trace.second->pos );


						if (screenpos.x != 0)
						{
							if (screenpos.y != 0)
							{
								ImVec2 other_player( screenpos.x, screenpos.y );

								draw->AddText( other_player, trace.second->color, str.c_str ( ) );
							}
						}
					}
				}
			}
		}
	}

	void TraceThread()
	{
		if (TraceVectorImpl.size() >= 1)
		{
			for (auto& trace : TraceVectorImpl)
			{
				if (!trace.second->raid)
				{
					trace.second->time++;
					if (trace.second->time >= 1000)
					{
						TraceVectorImpl.erase(trace.first);
					}
					else
					{
						auto draw = ImGui::GetBackgroundDrawList();

						auto screenpos = rust::WorldToScreen(trace.second->pos);

						ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(screenpos.x, screenpos.y), 10, ImColor(255, 0, 0, 90), 100.0f);
						ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(screenpos.x, screenpos.y), 10, ImColor(255, 0, 0, 0), 100.0f);
					}
				}
			}
		}
	}

	void ColorEditor(bool show, ImColor* object, std::string object_name)
	{
		if (!object) return;
		float col[4] = { object->Value.x, object->Value.y, object->Value.z, object->Value.w };
		if (show)
		{
			if (ImGui::ColorEdit4(object_name.c_str(), col, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar)) {
				*object = ImColor(col[0], col[1], col[2], col[3]);
			}
		}	
	}

	namespace ores
	{
		bool enable = false;
		bool showdistance = false;
		int maxdistance = 1000;
		bool drawname = false;
		bool metal = false;
		bool sulfur = false;
		bool stone = false;
		bool hotspot = false;
		ImColor metal_col = ImColor(255,255,255);
		ImColor sulfur_col = ImColor(255, 255, 255);
		ImColor stone_col = ImColor(255, 255, 255);
		ImColor hotspot_col = ImColor(255, 0, 0);
	}
	namespace loot
	{
		bool enable = false;
		bool TC = false;
		bool Loot_Crates = false;
		bool Loot_Barrels = false;
		bool Medical_crate = false;
		bool oil_Barrels = false;
		bool Military_crate = false;
		bool Supply_Drop = false;
		bool food_crate = false;
		bool fuel_crate = false;
		bool mine_crate = false;
		bool Heli = false;
		bool Back_Pack = false;
		bool APC_crate = false;
		bool Vehicle_Parts = false;
		bool showdistance = false;
		int maxdistance = 1000;

		ImColor TC_col = ImColor(255, 255, 255);
		ImColor Loot_Crates_col = ImColor(255, 255, 255);
		ImColor Loot_Barrels_col = ImColor(255, 255, 255);
		ImColor Medical_crate_col = ImColor(255, 255, 255);
		ImColor oil_Barrels_col = ImColor(255, 255, 255);
		ImColor Military_crate_col = ImColor(255, 255, 255);
		ImColor Supply_Drop_col = ImColor(106, 0, 255);
		ImColor food_crate_col = ImColor(255, 255, 255);
		ImColor fuel_crate_col = ImColor(255, 255, 255);
		ImColor mine_crate_col = ImColor(255, 255, 255);
		ImColor Heli_col = ImColor(255, 255, 255);
		ImColor Back_Pack_col = ImColor(255, 255, 255);
		ImColor APC_crate_col = ImColor(255, 255, 255);
		ImColor Vehicle_Parts_col = ImColor(255, 255, 255);
	}
	namespace collectable
	{
		bool enable = false;
		bool showdistance = false;
		int maxdistance = 1000;
		bool hemp = false;
		bool Mushroom = false;
		bool Pumpkin = false;
		bool Corn = false;
		bool Berry = false;
		bool Potato = false;
		bool Sulfur = false;
		bool Stone = false;
		bool Wood = false;
		bool Metal = false;
		ImColor hemp_col = ImColor(255, 255, 255);
		ImColor Mushroom_col = ImColor(255, 255, 255);
		ImColor Pumpkin_col = ImColor(255, 255, 255);
		ImColor Corn_col = ImColor(255, 255, 255);
		ImColor Berry_col = ImColor(255, 255, 255);
		ImColor Potato_col = ImColor(255, 255, 255);
		ImColor Sulfur_col = ImColor(255, 255, 255);
		ImColor Stone_col = ImColor(255, 255, 255);
		ImColor Wood_col = ImColor(255, 255, 255);
		ImColor Metal_col = ImColor(255, 255, 255);
	}
	namespace traps
	{
		bool enable = false;
		bool showdistance = false;
		int maxdistance = 1000;
		bool AutoTurret = false;
		bool Sam = false;
		bool Landmine = false;
		bool BearTrap = false;
		bool GunTrap = false;
		bool FlameTurret = false;

		ImColor AutoTurret_col = ImColor(255, 255, 255);
		ImColor Sam_col = ImColor(255, 255, 255);
		ImColor Landmine_col = ImColor(255, 255, 255);
		ImColor BearTrap_col = ImColor(255, 255, 255);
		ImColor GunTrap_col = ImColor(255, 255, 255);
		ImColor FlameTurret_col = ImColor(255, 255, 255);
	}
	namespace animals
	{
		bool enable = false;
		bool showdistance = false;
		int maxdistance = 1000;
		bool Bear = false;
		bool Boar = false;
		bool Chicken = false;
		bool Horse = false;
		bool Stag = false;
		bool Wolf = false;
		bool Zombie = false;
		ImColor Bear_col = ImColor(255, 255, 255);
		ImColor Boar_col = ImColor(255, 255, 255);
		ImColor Chicken_col = ImColor(255, 255, 255);
		ImColor Horse_col = ImColor(255, 255, 255);
		ImColor Stag_col = ImColor(255, 255, 255);
		ImColor Wolf_col = ImColor(255, 255, 255);
		ImColor Zombie_col = ImColor(255, 255, 255);
	}
	namespace items
	{
		bool enable = false;
		bool showdistance = false;
		int maxdistance = 1000;
		bool SleepingBag = false;
		bool large_wood_storage = false;
		bool furnace = false;
		bool large_furnace = false;
		bool Dropped_item = false;
		bool large_battery = false;
		bool medium_battery = false;
		bool small_battery = false;
		bool C4 = false;
		bool Satchel = false;
		bool Fire_Rocket = false;
		bool Rocket = false;
		bool HV_Rocket = false;
		bool trace_rockets = false;
		ImColor large_battery_col = ImColor(255, 255, 255);
		ImColor medium_battery_col = ImColor(255, 255, 255);
		ImColor small_battery_col = ImColor(255, 255, 255);
		ImColor large_wood_storage_col = ImColor(255, 255, 255);
		ImColor large_furnace_col = ImColor(255, 255, 255);
		ImColor furnace_col = ImColor(255, 255, 255);
		ImColor SleepingBag_col = ImColor(255, 255, 255);
		ImColor Dropped_item_col = ImColor(255, 255, 255);
		ImColor C4_col = ImColor(255, 255, 255);
		ImColor Satchel_col = ImColor(255, 255, 255);
		ImColor Fire_Rocket_col = ImColor(255, 255, 255);
		ImColor Rocket_col = ImColor(255, 255, 255);
		ImColor HV_Rocket_col = ImColor(255, 255, 255);
	}
	namespace vehicles
	{
		bool enable = false;
		bool showdistance = false;
		int maxdistance = 1000;
		bool patrolhelicopter = false;
		bool MiniCopter = false;
		bool ScrapTransportHelicopter = false;
		bool APC = false;
		ImColor patrolhelicopter_col = ImColor(255, 255, 255);
		ImColor MiniCopter_col = ImColor(255, 255, 255);
		ImColor ScrapTransportHelicopter_col = ImColor(255, 255, 255);
		ImColor APC_col = ImColor(255, 255, 255);
	}
	void EntityESP::Render()
	{
		if (ImGui::BeginTabBar(XR("entity")))
		{
			if (ImGui::BeginTabItem(XR("Ores")))
			{
				ImGui::BeginChild(XR("##opt"), ImVec2(ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y), false, ImGuiWindowFlags_NoScrollbar);
				ImGui::Checkbox(XR("Enable"), &ores::enable);
				ImGui::Checkbox(XR("Metal"), &ores::metal);
				ImGui::Checkbox(XR("Sulfur"), &ores::sulfur);
				ImGui::Checkbox(XR("Stone"), &ores::stone);
				ImGui::Checkbox(XR("Hot Spot"), &ores::hotspot);
				ImGui::Checkbox(XR("Distance"), &ores::showdistance);
				ImGui::EndChild();

				ImGui::SameLine();

				ImGui::BeginChild(XR("##opt2"), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));
				ColorEditor(ores::metal , &ores::metal_col, XR("Metal"));
				ColorEditor(ores::sulfur , &ores::sulfur_col, XR("Sulfur"));
				ColorEditor(ores::stone , &ores::stone_col, XR("Stone"));
				ColorEditor(ores::hotspot , &ores::hotspot_col, XR("Hot Spot"));
				ImGui::SetNextItemWidth(120);
				ImGui::SliderInt(XR("Distance"), &ores::maxdistance, 0, 1000);
				ImGui::EndChild();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(XR("Loot")))
			{
				ImGui::BeginChild(XR("##opt"), ImVec2(ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y), false, ImGuiWindowFlags_NoScrollbar);

				ImGui::Checkbox(XR("Enable"), &loot::enable);
				ImGui::Checkbox(XR("TC"), &loot::TC);
				ImGui::Checkbox(XR("Loot Barrels"), &loot::Loot_Barrels);
				ImGui::SameLine();
				ImGui::Checkbox(XR("Oil Barrel"), &loot::oil_Barrels);
				ImGui::Checkbox(XR("Loot Crates"), &loot::Loot_Crates);
				ImGui::SameLine();
				ImGui::Checkbox(XR("Military Crate"), &loot::Military_crate);
				ImGui::Checkbox(XR("Food Crate"), &loot::food_crate);
				ImGui::SameLine();
				ImGui::Checkbox(XR("Fuel Crate"), &loot::fuel_crate);
				ImGui::Checkbox(XR("Medical Crate"), &loot::Medical_crate);
				ImGui::SameLine();
				ImGui::Checkbox(XR("Mine Crate"), &loot::mine_crate);
				ImGui::Checkbox(XR("APC Crate"), &loot::APC_crate);
				ImGui::SameLine();
				ImGui::Checkbox(XR("Vehicle Parts"), &loot::Vehicle_Parts);
				ImGui::Checkbox(XR("Back Pack"), &loot::Back_Pack);
				ImGui::SameLine();
				ImGui::Checkbox(XR("Supply Drop"), &loot::Supply_Drop);
				ImGui::Checkbox(XR("Distance"), &loot::showdistance);
				ImGui::SameLine();
				ImGui::Checkbox(XR("Heli Crate"), &loot::Heli);

				ImGui::EndChild();

				ImGui::SameLine();

				ImGui::BeginChild(XR("##opt2"), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));

				ColorEditor(loot::TC, &loot::TC_col, XR("TC"));
				//ImGui::SameLine();
				ColorEditor(loot::Loot_Barrels, &loot::Loot_Barrels_col, XR("Loot Barrels"));
				ColorEditor(loot::oil_Barrels, &loot::oil_Barrels_col, XR("Oil Barrels"));
				//ImGui::SameLine();
				ColorEditor(loot::Loot_Crates, &loot::Loot_Crates_col, XR("Loot Crates"));
				ColorEditor(loot::Military_crate, &loot::Military_crate_col, XR("Military Crate"));
				//ImGui::SameLine();
				ColorEditor(loot::food_crate, &loot::food_crate_col, XR("Food Crate"));
				ColorEditor(loot::fuel_crate, &loot::fuel_crate_col, XR("Fuel Crate"));
				//ImGui::SameLine();
				ColorEditor(loot::Medical_crate, &loot::Medical_crate_col, XR("Medical crate"));
				ColorEditor(loot::mine_crate, &loot::mine_crate_col, XR("Mine Crate"));
				//ImGui::SameLine();
				ColorEditor(loot::APC_crate, &loot::APC_crate_col, XR("APC Crate"));
				ColorEditor(loot::Vehicle_Parts, &loot::Vehicle_Parts_col, XR("Vehicle Parts"));
				//ImGui::SameLine();
				ColorEditor(loot::Back_Pack, &loot::Back_Pack_col, XR("Back Pack"));
				ColorEditor(loot::Supply_Drop, &loot::Supply_Drop_col, XR("Supply Drop"));
				//ImGui::SameLine();
				ColorEditor(loot::Heli, &loot::Heli_col, XR("Heli Crate"));

				ImGui::SetNextItemWidth(120);
				ImGui::SliderInt(XR("Distance"), &loot::maxdistance, 0, 1000);
				ImGui::EndChild();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(XR("Collectables")))
			{
				ImGui::BeginChild(XR("##opt"), ImVec2(ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y), false, ImGuiWindowFlags_NoScrollbar);
				ImGui::Checkbox(XR("Enable"), &collectable::enable);
				ImGui::Checkbox(XR("Hemp"), &collectable::hemp);
				ImGui::SameLine();
				ImGui::Checkbox(XR("Mushroom Cluster"), &collectable::Mushroom);
				ImGui::Checkbox(XR("Pumpkin"), &collectable::Pumpkin);
				ImGui::SameLine();
				ImGui::Checkbox(XR("Berry"), &collectable::Berry);
				ImGui::Checkbox(XR("Corn"), &collectable::Corn);
				ImGui::SameLine();
				ImGui::Checkbox(XR("Potato"), &collectable::Potato);
				ImGui::Checkbox(XR("Sulfur"), &collectable::Sulfur);
				ImGui::SameLine();
				ImGui::Checkbox(XR("Stone"), &collectable::Stone);
				ImGui::Checkbox(XR("Wood"), &collectable::Wood);
				ImGui::SameLine();
				ImGui::Checkbox(XR("Metal"), &collectable::Metal);

				ImGui::Checkbox(XR("Distance"), &collectable::showdistance);
				ImGui::EndChild();
				ImGui::SameLine();
				ImGui::BeginChild(XR("##opt2"), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));

				ColorEditor(collectable::hemp, &collectable::hemp_col, XR("Hemp"));
				ColorEditor(collectable::Mushroom, &collectable::Mushroom_col, XR("Mushroom Cluster"));
				ColorEditor(collectable::Pumpkin, &collectable::Pumpkin_col, XR("Pumpkin"));
				ColorEditor(collectable::Berry, &collectable::Berry_col, XR("Berry"));
				ColorEditor(collectable::Corn, &collectable::Corn_col, XR("Corn"));
				ColorEditor(collectable::Potato, &collectable::Potato_col, XR("Potato"));
				ColorEditor(collectable::Sulfur, &collectable::Sulfur_col, XR("Sulfur"));
				ColorEditor(collectable::Stone, &collectable::Stone_col, XR("Stone"));
				ColorEditor(collectable::Wood, &collectable::Wood_col, XR("Wood"));
				ImGui::SameLine();
				ColorEditor(collectable::Metal, &collectable::Metal_col, XR("Metal"));

				ImGui::SetNextItemWidth(120);
				ImGui::SliderInt(XR("Distance"), &collectable::maxdistance, 0, 1000);
				ImGui::EndChild();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(XR("Traps")))
			{
				ImGui::BeginChild(XR("##opt"), ImVec2(ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y), false, ImGuiWindowFlags_NoScrollbar);
				ImGui::Checkbox(XR("Enable"), &traps::enable);

				ImGui::Checkbox(XR("AutoTurret"), &traps::AutoTurret);
				ImGui::Checkbox(XR("Sam Site"), &traps::Sam);
				ImGui::Checkbox(XR("Landmine"), &traps::Landmine);
				ImGui::Checkbox(XR("BearTrap"), &traps::BearTrap);
				ImGui::Checkbox(XR("GunTrap"), &traps::GunTrap);
				ImGui::Checkbox(XR("FlameTurret"), &traps::FlameTurret);

				ImGui::Checkbox(XR("Distance"), &traps::showdistance);
				ImGui::EndChild();
				ImGui::SameLine();

				ImGui::BeginChild(XR("##opt2"), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));

				ColorEditor(traps::AutoTurret, &traps::AutoTurret_col, XR("AutoTurret"));
				ColorEditor(traps::Sam, &traps::Sam_col, XR("Sam Site"));
				ColorEditor(traps::Landmine, &traps::Landmine_col, XR("Landmine"));
				ColorEditor(traps::BearTrap, &traps::BearTrap_col, XR("BearTrap"));
				ColorEditor(traps::GunTrap, &traps::GunTrap_col, XR("GunTrap"));
				ColorEditor(traps::FlameTurret, &traps::FlameTurret_col, XR("FlameTurret"));

				ImGui::SetNextItemWidth(120);
				ImGui::SliderInt(XR("Distance"), &traps::maxdistance, 0, 1000);
				ImGui::EndChild();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(XR("Animals")))
			{
				ImGui::BeginChild(XR("##opt"), ImVec2(ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y), false, ImGuiWindowFlags_NoScrollbar);

				ImGui::Checkbox(XR("Enable"), &animals::enable);

				ImGui::Checkbox(XR("Boar"), &animals::Boar);
				ImGui::Checkbox(XR("Bear"), &animals::Bear);
				ImGui::Checkbox(XR("Chicken"), &animals::Chicken);
				ImGui::Checkbox(XR("Horse"), &animals::Horse);
				ImGui::Checkbox(XR("Stag"), &animals::Stag);
				ImGui::Checkbox(XR("Zombie"), &animals::Zombie);

				ImGui::Checkbox(XR("Distance"), &animals::showdistance);
				ImGui::EndChild();

				ImGui::SameLine();

				ImGui::BeginChild(XR("##opt2"), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));

				ColorEditor(animals::Boar, &animals::Boar_col, XR("Boar"));
				ColorEditor(animals::Bear, &animals::Bear_col, XR("Bear"));
				ColorEditor(animals::Chicken, &animals::Chicken_col, XR("Chicken"));
				ColorEditor(animals::Horse, &animals::Horse_col, XR("Horse"));
				ColorEditor(animals::Stag, &animals::Stag_col, XR("Stag"));
				ColorEditor(animals::Zombie, &animals::Zombie_col, XR("Zombie"));

				ImGui::SetNextItemWidth(120);
				ImGui::SliderInt(XR("Distance"), &animals::maxdistance, 0, 1000);
				ImGui::EndChild();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(XR("Items")))
			{
				ImGui::BeginChild(XR("##opt"), ImVec2(ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y), false, ImGuiWindowFlags_NoScrollbar);

				ImGui::Checkbox(XR("Enable"), &items::enable);

				ImGui::Checkbox(XR("SleepingBag"), &items::SleepingBag);
				ImGui::SameLine();
				ImGui::Checkbox(XR("Large Wood Box"), &items::large_wood_storage);
				ImGui::Checkbox(XR("Furnace"), &items::furnace);
				ImGui::SameLine();
				ImGui::Checkbox(XR("Large Furnace"), &items::large_furnace);
				ImGui::Checkbox(XR("Dropped item"), &items::Dropped_item);
				ImGui::SameLine();

				ImGui::Checkbox(XR("Large Battery"), &items::large_battery);
				ImGui::Checkbox(XR("Medium Battery"), &items::medium_battery);
				ImGui::SameLine(),
				ImGui::Checkbox(XR("Slamm Battery"), &items::small_battery);

				ImGui::Checkbox(XR("C4"), &items::C4);
				ImGui::SameLine();
				ImGui::Checkbox(XR("Satchel"), &items::Satchel);
				ImGui::Checkbox(XR("Rocket"), &items::Rocket);
				ImGui::SameLine();
				ImGui::Checkbox(XR("Fire Rocket"), &items::Fire_Rocket);
				ImGui::Checkbox(XR("HV Rocket"), &items::HV_Rocket);

				ImGui::Checkbox(XR("Distance"), &items::showdistance);
				ImGui::EndChild();

				ImGui::SameLine();

				ImGui::BeginChild(XR("##opt2"), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));

				if (items::Rocket || items::Fire_Rocket || items::HV_Rocket)
				{
					ImGui::Checkbox(XR("Trace Rockets"), &items::trace_rockets);
				}

				ColorEditor(items::SleepingBag, &items::SleepingBag_col, XR("SleepingBag"));
				ColorEditor(items::large_wood_storage, &items::large_wood_storage_col, XR("Large Wood Box"));
				ColorEditor(items::furnace, &items::furnace_col, XR("Large Wood Box"));
				ColorEditor(items::large_furnace, &items::large_furnace_col, XR("Large Wood Box"));
				ColorEditor(items::Dropped_item, &items::Dropped_item_col, XR("Dropped item"));

				ColorEditor(items::large_battery, &items::large_battery_col, XR("Large Battery"));
				ColorEditor(items::medium_battery, &items::medium_battery_col, XR("Medium Battery"));
				ColorEditor(items::small_battery, &items::small_battery_col, XR("Small Battery"));


				ColorEditor(items::C4, &items::C4_col, XR("C4"));
				ColorEditor(items::Rocket, &items::Rocket_col, XR("Rocket"));
				ColorEditor(items::Fire_Rocket, &items::Fire_Rocket_col, XR("Fire Rocket"));
				ColorEditor(items::HV_Rocket, &items::HV_Rocket_col, XR("HV Rocket"));

				ImGui::SetNextItemWidth(120);
				ImGui::SliderInt(XR("Distance"), &items::maxdistance, 0, 1000);
				ImGui::EndChild();

				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(XR("Vehicles")))
			{
				ImGui::BeginChild(XR("##opt"), ImVec2(ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y), false, ImGuiWindowFlags_NoScrollbar);
				ImGui::Checkbox(XR("Enable"), &vehicles::enable);

				ImGui::Checkbox(XR("MiniCopter"), &vehicles::MiniCopter);
				ImGui::Checkbox(XR("Scrap Transport Helicopter"), &vehicles::ScrapTransportHelicopter);
				ImGui::Checkbox(XR("Patrol Helicopter"), &vehicles::patrolhelicopter);
				ImGui::Checkbox(XR("APC"), &vehicles::APC);
				ImGui::Checkbox(XR("Distance"), &vehicles::showdistance);
				ImGui::EndChild();

				ImGui::SameLine();

				ImGui::BeginChild(XR("##opt2"), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));

				ColorEditor(vehicles::MiniCopter, &vehicles::MiniCopter_col, XR("MiniCopter"));
				ColorEditor(vehicles::ScrapTransportHelicopter, &vehicles::ScrapTransportHelicopter_col, XR("Scrap Transport Helicopter"));
				ColorEditor(vehicles::patrolhelicopter, &vehicles::patrolhelicopter_col, XR("Patrol Helicopter"));
				ColorEditor(vehicles::APC, &vehicles::APC_col, XR("APC"));

				ImGui::SetNextItemWidth(120);
				ImGui::SliderInt(XR("Distance"), &vehicles::maxdistance, 0, 1000);
				ImGui::EndChild();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(XR("Raid")))
			{
				ImGui::BeginChild(XR("##opt"), ImVec2(ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y), false, ImGuiWindowFlags_NoScrollbar);
				ImGui::Checkbox(XR("Enable"), &raid::enable);

				ImGui::Checkbox(XR("Raid ESP"), &raid::raid_esp);
				ImGui::Checkbox(XR("Home Base Raid ESP"), &raid::raid_home_esp);
				if (raid::raid_home_esp)
				{
					if (ImGui::Button(XR("Set Home"))) {
						rust::BaseLocalPlayer->UpdatePosition();
						raid::home_base = rust::BaseLocalPlayer->GetPosition();
					}
					ImGui::Checkbox(XR("Hide Home ESP"), &raid::hide_base_objects);
				}
				ImGui::Checkbox(XR("Distance"), &raid::showdistance);
				ImGui::EndChild();
			}
			ImGui::EndTabBar();
		}
	}
	bool nn = false;
	void EntityESP::Thread() {
		LoadObjectNames();
		TraceThread();
		RaidThread();
		auto draw = ImGui::GetBackgroundDrawList();
		if (ores::enable || loot::enable || collectable::enable || traps::enable || animals::enable || items::enable || vehicles::enable || raid::enable)
		{
			for (int i = 0; i < rust::BaseNetworkableC->GetObjectSize(); i++)
			{
				uintptr_t element = driver::read<uintptr_t>(rust::BaseNetworkableC->GetObjectList() + (0x20 + (i * 8)));//rust::BaseNetworkableC->GetElement(i);
				if (!element)
				{
					continue;
				}

				/*
				class BaseNetworkable
	// Token: 0x040028A2 RID: 10402
	[Token(Token = "0x40028A2")]
	[FieldOffset(Offset = "0x48")]
	private string _prefabName;
				*/
				uint64_t element_name = driver::read<uintptr_t>(element + 0x48);

				std::string pName = driver::read_unicode(element_name + 0x14, 100);
				if (pName.empty())
					continue;

/*
				if (pName == "core/foundation/foundation.prefabassets/prefabs/building")
					continue;
				if (pName == "assets/prefabs/building core/foundation/foundation.prefab")
					continue;
*/
				
				
				if (ObjectsNames.find(pName) == ObjectsNames.end())
				{
					//std::cout << "Skiped: " << pName << std::endl;
					continue;
				}
				
				
				


				uintptr_t base_mono_object = driver::read<uintptr_t>(element + 0x10);
				if (!base_mono_object)
				{
					global::print(XR("No base object"));
					continue;
				}
				uintptr_t object = driver::read<uintptr_t>(base_mono_object + 0x30);
				if (!object)
				{
					global::print(XR("No object"));
					continue;
				}
				uintptr_t objectClass = driver::read<uintptr_t>(object + 0x30);
				if (!objectClass)
				{
					global::print(XR("No objectClass"));
					continue;
				}

				/*
				uintptr_t pObjName = driver::read<uintptr_t>(object + 0x60);
				std::string object_name = driver::read_ascii(pObjName, 128);
				*/

				Vector3 position = driver::read<Vector3>(rust::BaseNetworkableC->GetObjectComponent(objectClass) + 0x90);
				rust::BaseLocalPlayer->UpdatePosition();

				if (position == rust::BaseLocalPlayer->GetPosition())
					continue;

				int distance = (int)Vector3::Distance(position, rust::BaseLocalPlayer->GetPosition());



				if (ores::enable)
				{
					if (distance > ores::maxdistance)
						continue;

					std::string str = ObjectsNames[pName];

					if (ores::hotspot && str == XR("Hot Spot"))
					{
						auto screenpos = rust::WorldToScreen(position);


						if (screenpos.x == 0)
							continue;
						if (screenpos.y == 0)
							continue;

						if (distance < 30)
						{
							ImColor lpm = ores::hotspot_col;
							lpm.Value.w = 90;
							ImColor impl = ores::hotspot_col;
							ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(screenpos.x, screenpos.y), (10 - (distance / 100)), lpm, 100.0f);
							ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(screenpos.x, screenpos.y), (10 - (distance / 100)), impl, 100.0f);
						}
					}

					if (ores::metal && str == XR("Metal Ore"))
					{
						RenderObject(str, distance, position, ores::showdistance, draw, ores::metal_col);
					}
					if (ores::sulfur && str == XR("Sulfur Ore"))
					{
						RenderObject(str, distance, position, ores::showdistance, draw, ores::sulfur_col);
					}
					if (ores::stone && str == XR("Stone Ore"))
					{
						RenderObject(str, distance, position, ores::showdistance, draw, ores::stone_col);
					}

					//if (ores::hotspot && str == XR("Hot Spot"))
					//{
					//	RenderObject(str, distance, position, ores::showdistance, draw);
					//}
				}
				if (loot::enable)
				{
					if (distance > loot::maxdistance)
						continue;

					std::string str = ObjectsNames[pName];

					if (str == XR("TC") ||
						str == XR("Food Crate") ||
						str == XR("Fuel Crate") ||
						str == XR("Medical Crate") ||
						str == XR("Mine Crate") ||
						str == XR("Military Crate") ||
						str == XR("APC Crate") ||
						str == XR("Loot Crate") ||
						str == XR("Loot Barrel") ||
						str == XR("Oil Barrel") ||
						str == XR("Supply Drop") ||
						str == XR("Vehicle Parts") ||
						str == XR("Back Pack"))
					{

						if (loot::TC && str == XR("TC"))
						{
							RenderObject(str, distance, position, loot::showdistance, draw, loot::TC_col);
						}
						if (loot::Heli && str == XR("Heli Crate"))
						{
							RenderObject(str, distance, position, loot::showdistance, draw, loot::Heli_col);
						}
						if (loot::food_crate && str == XR("Food Crate"))
						{
							RenderObject(str, distance, position, loot::showdistance, draw, loot::food_crate_col);
						}
						if (loot::fuel_crate && str == XR("Fuel Crate"))
						{
							RenderObject(str, distance, position, loot::showdistance, draw, loot::fuel_crate_col);
						}
						if (loot::Medical_crate && str == XR("Medical Crate"))
						{
							RenderObject(str, distance, position, loot::showdistance, draw, loot::Medical_crate_col);
						}
						if (loot::mine_crate && str == XR("Mine Crate"))
						{
							RenderObject(str, distance, position, loot::showdistance, draw, loot::mine_crate_col);
						}
						if (loot::Military_crate && str == XR("Military Crate"))
						{
							RenderObject(str, distance, position, loot::showdistance, draw, loot::Military_crate_col);
						}
						if (loot::APC_crate && str == XR("APC Crate"))
						{
							RenderObject(str, distance, position, loot::showdistance, draw, loot::APC_crate_col);
						}
						if (loot::Loot_Crates && str == XR("Loot Crate"))
						{
							RenderObject(str, distance, position, loot::showdistance, draw, loot::Loot_Crates_col);
						}
						if (loot::Loot_Barrels && str == XR("Loot Barrel"))
						{
							RenderObject(str, distance, position, loot::showdistance, draw, loot::Loot_Barrels_col);
						}
						if (loot::oil_Barrels && str == XR("Oil Barrel"))
						{
							RenderObject(str, distance, position, loot::showdistance, draw, loot::oil_Barrels_col);
						}
						if (loot::Supply_Drop && str == XR("Supply Drop"))
						{
							RenderObject(str, distance, position, loot::showdistance, draw, loot::Supply_Drop_col);
						}
						if (loot::Vehicle_Parts && str == XR("Vehicle Parts"))
						{
							RenderObject(str, distance, position, loot::showdistance, draw, loot::Vehicle_Parts_col);
						}
						if (loot::Back_Pack && str == XR("Back Pack"))
						{
							RenderObject(str, distance, position, loot::showdistance, draw, loot::Back_Pack_col);
						}
					}

				}
				if (collectable::enable)
				{
					if (distance > collectable::maxdistance)
						continue;

					std::string str = ObjectsNames[pName];

					if (str == XR("Hemp") ||
						str == XR("Mushroom Cluster") ||
						str == XR("Pumpkin") ||
						str == XR("Mush") ||
						str == XR("Corn") ||
						str == XR("Berry") ||
						str == XR("Sulfur Collectable") ||
						str == XR("Stone Collectable") ||
						str == XR("Wood Collectable") ||
						str == XR("Metal Collectable"))
					{
						if (collectable::hemp && str == XR("Hemp"))
						{
							RenderObject(str, distance, position, collectable::showdistance, draw, collectable::hemp_col);
						}
						if (collectable::Mushroom && str == XR("Mushroom Cluster"))
						{
							RenderObject(str, distance, position, collectable::showdistance, draw, collectable::Mushroom_col);
						}
						if (collectable::Pumpkin && str == XR("Pumpkin"))
						{
							RenderObject(str, distance, position, collectable::showdistance, draw, collectable::Pumpkin_col);
						}
						if (collectable::Berry && str == XR("Berry"))
						{
							RenderObject(str, distance, position, collectable::showdistance, draw, collectable::Berry_col);
						}
						if (collectable::Corn && str == XR("Corn"))
							RenderObject(str, distance, position, collectable::showdistance, draw, collectable::Corn_col);

						if (collectable::Potato && str == XR("Potato"))
							RenderObject(str, distance, position, collectable::showdistance, draw, collectable::Potato_col);

						if (collectable::Sulfur && str == XR("Sulfur Collectable"))
							RenderObject(str, distance, position, collectable::showdistance, draw, collectable::Sulfur_col);

						if (collectable::Stone && str == XR("Stone Collectable"))
							RenderObject(str, distance, position, collectable::showdistance, draw, collectable::Stone_col);

						if (collectable::Wood && str == XR("Wood Collectable"))
							RenderObject(str, distance, position, collectable::showdistance, draw, collectable::Wood_col);

						if (collectable::Metal && str == XR("Metal Collectable"))
							RenderObject(str, distance, position, collectable::showdistance, draw, collectable::Metal_col);
					}

				}
				if (traps::enable)
				{
					if (distance > traps::maxdistance)
						continue;

					std::string str = ObjectsNames[pName];

					if (traps::AutoTurret && str == XR("AutoTurret"))
					{
						RenderObject(str, distance, position, traps::showdistance, draw, traps::AutoTurret_col);
					}
					if (traps::Sam && str == XR("Sam Site"))
					{
						RenderObject(str, distance, position, traps::showdistance, draw, traps::Sam_col);
					}
					if (traps::Landmine && str == XR("Landmine"))
					{
						RenderObject(str, distance, position, traps::showdistance, draw, traps::Landmine_col);
					}
					if (traps::BearTrap && str == XR("BearTrap"))
					{
						RenderObject(str, distance, position, traps::showdistance, draw, traps::BearTrap_col);
					}
					if (traps::GunTrap && str == XR("GunTrap"))
					{
						RenderObject(str, distance, position, traps::showdistance, draw, traps::GunTrap_col);
					}
					if (traps::FlameTurret && str == XR("FlameTurret"))
					{
						RenderObject(str, distance, position, traps::showdistance, draw, traps::FlameTurret_col);
					}

				}
				if (animals::enable)
				{
					if (distance > animals::maxdistance)
						continue;

					std::string str = ObjectsNames[pName];

					if (animals::Bear && str == XR("Bear"))
					{
						RenderObject(str, distance, position, animals::showdistance, draw, animals::Bear_col);
					}
					if (animals::Bear && str == XR("Boar"))
					{
						RenderObject(str, distance, position, animals::showdistance, draw, animals::Boar_col);
					}
					if (animals::Chicken && str == XR("Chicken"))
					{
						RenderObject(str, distance, position, animals::showdistance, draw, animals::Chicken_col);
					}
					if (animals::Horse && str == XR("Horse"))
					{
						RenderObject(str, distance, position, animals::showdistance, draw, animals::Horse_col);
					}
					if (animals::Stag && str == XR("Stag"))
					{
						RenderObject(str, distance, position, animals::showdistance, draw, animals::Stag_col);
					}
					if (animals::Zombie && str == XR("Zombie"))
					{
						RenderObject(str, distance, position, animals::showdistance, draw, animals::Zombie_col);
					}

				}
				if (items::enable)
				{
					if (distance > items::maxdistance)
						continue;

					std::string str = ObjectsNames[pName];

					if (items::SleepingBag && str == XR("SleepingBag"))
					{
						RenderObject(str, distance, position, items::showdistance, draw, items::SleepingBag_col);
					}
					if (items::furnace && str == XR("Furnace"))
					{
						RenderObject(str, distance, position, items::showdistance, draw, items::furnace_col);
					}
					if (items::large_furnace && str == XR("Large Furnace"))
					{
						RenderObject(str, distance, position, items::showdistance, draw, items::large_furnace_col);
					}

					if (items::large_battery && str == XR("Large Battery"))
					{
						RenderObject(str, distance, position, items::showdistance, draw, items::large_battery_col);
					}
					if (items::medium_battery && str == XR("Medium Battery"))
					{
						RenderObject(str, distance, position, items::showdistance, draw, items::medium_battery_col);
					}
					if (items::small_battery && str == XR("Small Battery"))
					{
						RenderObject(str, distance, position, items::showdistance, draw, items::small_battery_col);
					}

					if (items::large_wood_storage && str == XR("Large Wood Storage"))
					{
						RenderObject(str, distance, position, items::showdistance, draw, items::large_wood_storage_col);
					}
					if (items::Dropped_item && str == XR("Dropped item"))
					{
						RenderObject(str, distance, position, items::showdistance, draw, items::Dropped_item_col);
					}
					if (items::Dropped_item && str == XR("Item"))
					{
						RenderObject(str, distance, position, items::showdistance, draw, items::Dropped_item_col);
					}
					if (items::C4 && str == XR("C4"))
					{
						RenderObject(str, distance, position, items::showdistance, draw, items::C4_col);
					}
					if (items::Satchel && str == XR("Satchel"))
					{
						RenderObject(str, distance, position, items::showdistance, draw, items::Satchel_col);
					}
					if (items::Rocket && str == XR("Rocket"))
					{
						if (items::trace_rockets)
						{
							RenderObjectWithTrace(str, distance, position, items::showdistance, draw, items::trace_rockets, objectClass);
						}
						else
						{
							RenderObject(str, distance, position, items::showdistance, draw, items::Rocket_col);
						}
					}
					if (items::Fire_Rocket && str == XR("Fire Rocket"))
					{
						if (items::trace_rockets)
						{
							RenderObjectWithTrace(str, distance, position, items::showdistance, draw, items::trace_rockets, objectClass);
						}
						else
						{
							RenderObject(str, distance, position, items::showdistance, draw, items::Fire_Rocket_col);
						}
					}
					if (items::HV_Rocket && str == XR("HV Rocket"))
					{
						if (items::trace_rockets)
						{
							RenderObjectWithTrace(str, distance, position, items::showdistance, draw, items::trace_rockets, objectClass);
						}
						else
						{
							RenderObject(str, distance, position, items::showdistance, draw, items::HV_Rocket_col);
						}
					}

				}
				if (vehicles::enable)
				{
					if (distance > vehicles::maxdistance)
						continue;

					std::string str = ObjectsNames[pName];

					if (vehicles::APC && str == XR("APC"))
					{
						RenderObject(str, distance, position, vehicles::showdistance, draw, vehicles::APC_col);
					}
					if (vehicles::MiniCopter && str == XR("MiniCopter"))
					{
						RenderObject(str, distance, position, vehicles::showdistance, draw, vehicles::MiniCopter_col);
					}
					if (vehicles::ScrapTransportHelicopter && str == XR("Scrap Transport Helicopter"))
					{
						RenderObject(str, distance, position, vehicles::showdistance, draw, vehicles::ScrapTransportHelicopter_col);
					}
					if (vehicles::patrolhelicopter && str == XR("Patrol Helicopter"))
					{
						RenderObject(str, distance, position, vehicles::patrolhelicopter, draw, vehicles::patrolhelicopter_col);
					}
				}
				if (raid::enable)
				{
					if (distance == 0)
						continue;

					if (raid::raid_esp)
					{
						std::string str = ObjectsNames[pName];
						if (str == XR("C4"))
						{
							RenderRaidObject(str, distance, position, raid::showdistance, draw, objectClass);
						}
						if (str == XR("Satchel"))
						{
							RenderRaidObject(str, distance, position, raid::showdistance, draw, objectClass);
						}
						if (str == XR("Rocket"))
						{
							RenderRaidObject(str, distance, position, raid::showdistance, draw, objectClass);
						}
						if (str == XR("Fire Rocket"))
						{
							RenderRaidObject(str, distance, position, raid::showdistance, draw, objectClass);
						}
						if (str == XR("HV Rocket"))
						{
							RenderRaidObject(str, distance, position, raid::showdistance, draw, objectClass);
						}
					}
					if (raid::raid_home_esp)
					{
						std::string str = ObjectsNames[pName];
						if (str == XR("C4"))
						{
							RenderRaidHomeObject(str, distance, position, raid::showdistance, raid::home_base, draw, objectClass);
						}
						if (str == XR("Satchel"))
						{
							RenderRaidHomeObject(str, distance, position, raid::showdistance, raid::home_base, draw, objectClass);
						}
						if (str == XR("Rocket"))
						{
							RenderRaidHomeObject(str, distance, position, raid::showdistance, raid::home_base, draw, objectClass);
						}
						if (str == XR("Fire Rocket"))
						{
							RenderRaidHomeObject(str, distance, position, raid::showdistance, raid::home_base, draw, objectClass);
						}
						if (str == XR("HV Rocket"))
						{
							RenderRaidHomeObject(str, distance, position, raid::showdistance, raid::home_base, draw, objectClass);
						}
					}
				}

				///https://www.unknowncheats.me/forum/rust/463853-name-field-object-using-offset.html
				///https://github.com/OrangeWulf/Rust-Docs/blob/master/Entities.md

			}
		}
	
	}

}