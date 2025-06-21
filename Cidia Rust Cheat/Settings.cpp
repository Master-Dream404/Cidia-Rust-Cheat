#include "Settings.h"
#include "imgui/imgui.h"
#include "rust.h"
#include <map>
#include "Hotkey.h"
namespace Settings
{
	namespace orig
	{
		float NightLightIntensity = 0;
		float NightAmbientMultiplier = 0;
		float DayAmbientMultiplier = 0;
		float fov = 0;
	}
	namespace config
	{
		//kan ikke stave?
		//bool panik = false;//panic
		bool brightnight = false;
		bool BrightCaves = false;
		int fov = 0;
		float modfov;
		HotKeys* HotKey = new HotKeys();
		HotKeys* panik = new HotKeys();
	}
	void Settings::Render() {
		ImGui::Checkbox(XR("Bright Nights"), &config::brightnight);
		ImGui::Checkbox(XR("Bright Caves"), &config::BrightCaves);
		ImGui::SetNextItemWidth(120);
		ImGui::SliderInt(XR("Field of view"), &config::fov, 0, 200);
		ImGui::Checkbox(XR("Zoom on key"), &config::HotKey->toggel);
		ImGui::SameLine();
		GUI::HotKey(config::HotKey, ImVec2(23, 23));

		ImGui::Checkbox(XR("Panic"), &config::panik->toggel);
		ImGui::SameLine();
		GUI::HotKey(config::panik, ImVec2(23, 23));
	}
	void Settings::Threads() {
		if (orig::fov == 0)
		{
			/*
			config::fov = rust::ConvarGraphicsC->GetFov();
			orig::fov = rust::ConvarGraphicsC->GetFov();
			*/
		}
		if (config::modfov != config::fov)
		{
			rust::ConvarGraphicsC->WriteFOV(config::fov);
			config::modfov = config::fov;
		}
		if (config::brightnight)
		{
			rust::Sky->WriteNightLightIntensity(25.0f);
			rust::Sky->WriteNightAmbientMultiplier(4.0f);
		}
		if (config::BrightCaves)
		{
			rust::Sky->WriteDayAmbientMultiplier(2.0f);
		}

		if (config::HotKey->toggel)
		{
			if (config::HotKey->key != 0)
			{
				if (GetAsyncKeyState(config::HotKey->key) & 0x80000)
				{
					rust::ConvarGraphicsC->WriteFOV(35);
				}
				else
				{
					if (rust::ConvarGraphicsC->GetFov() != config::fov)
					{
						rust::ConvarGraphicsC->WriteFOV(config::fov);
					}
				}
			}
		}

		if (config::panik->toggel)
		{
			if (config::panik->key != 0)
			{
				if (GetAsyncKeyState(config::panik->key) & 0x80000)
				{
					exit(0x0);
				}
			}
		}
	}
}