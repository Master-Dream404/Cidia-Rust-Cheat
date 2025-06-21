#include "ui.h"
#include "imgui/imgui.h"
#include <m_includes/XorStr/XR.hpp>
#include "return_spoofer.hpp"
#include "rust.h"
#include "Aimbot.h"
#include "Visuals.h"
#include "EntityESP.h"
#include <thread>
#include "Settings.h"
#include "Miscellaneous.h"
#include "style.h"
namespace ui
{
	enum TAP : int
	{
		AIMBOT,
		VISUALS,
		ENTITYESP,
		Miscellaneous,
		Settings
	};
	bool ShowMenu = false;
	TAP selected_tap;
	void ui::Render() {
		if (ShowMenu)
		{
			style::Render();
			ImGui::SetNextWindowSize({ 630, 403 });
			ImGui::Begin(XR("Cidia"), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
			{
				if (ImGui::Button(XR("Aimbot"), ImVec2(ImGui::GetContentRegionAvail().x / 5, 33)))
				{
					selected_tap = TAP::AIMBOT;
				}
				ImGui::SameLine();
				if (ImGui::Button(XR("Player ESP"), ImVec2(ImGui::GetContentRegionAvail().x / 4, 33)))
				{
					selected_tap = TAP::VISUALS;
				}
				ImGui::SameLine();
				if (ImGui::Button(XR("Entity ESP"), ImVec2(ImGui::GetContentRegionAvail().x / 3, 33)))
				{
					selected_tap = TAP::ENTITYESP;
				}
				ImGui::SameLine();
				if (ImGui::Button(XR("Miscellaneous"), ImVec2(ImGui::GetContentRegionAvail().x / 2, 33)))
				{
					selected_tap = TAP::Miscellaneous;
				}
				ImGui::SameLine();
				if (ImGui::Button(XR("Settings"), ImVec2(ImGui::GetContentRegionAvail().x, 33)))
				{
					selected_tap = TAP::Settings;
				}

				switch (selected_tap)
				{
				case ui::AIMBOT:
					Aimbot::Render();
					break;
				case ui::VISUALS:
					Visuals::Render();
					break;
				case ui::ENTITYESP:
					EntityESP::Render();
					break;
				case ui::Miscellaneous:
					Miscellaneous::Render();
					break;
				case ui::Settings:
					Settings::Render();
					break;
				default:
					break;
				}

			}
			ImGui::End();
		}

	}

	bool ui::SetMenuState(bool state){
		ShowMenu = state;
		return ShowMenu == state ? true : false;
	}

/*
	std::thread rustThread([]() {
		rust::IntializeRust->Execute();
		rust::RefreshViewMatrix->Execute();
		Aimbot::Thread();
		Visuals::Thread();
		EntityESP::Thread();
		});
*/

	void ui::Threads() {
		//rust::IntializeRust->Execute();
		HWND Rust_HWND = FindWindow(NULL, XR(L"Rust"));
		if (Rust_HWND != NULL)
		{

			rust::PerServerVariables();

			Aimbot::Thread();
			Visuals::Thread();
			EntityESP::Thread();
			Settings::Threads();
			Miscellaneous::Threads();
		}
	}

}