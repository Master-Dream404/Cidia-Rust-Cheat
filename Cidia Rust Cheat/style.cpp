#include "style.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include <Windows.h>
#include <string>
#include <xcall_once.h>
#include "font.h"
#include "customfont.h"
namespace style
{
	std::once_flag s;
	void style::Render() {
		std::call_once(s, []{

			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();
			auto& style = ImGui::GetStyle();
			auto& colors = style.Colors;
/*

			io.IniFilename = nullptr;
			io.LogFilename = nullptr;
			io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
*/

/*
			ImFontConfig rubik;
			rubik.FontDataOwnedByAtlas = false;
			rubik.GlyphRanges = io.Fonts->GetGlyphRangesCyrillic();

			strcpy_s(rubik.Name, ("Rubik"));
			io.Fonts->AddFontFromMemoryTTF(const_cast<uint8_t*>(Rubik), sizeof(Rubik), 21.0f, &rubik);
*/


			static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

			ImFontConfig fontawesome2_cfg{};
			fontawesome2_cfg.FontDataOwnedByAtlas = false;
			fontawesome2_cfg.MergeMode = true;

			strcpy_s(fontawesome2_cfg.Name, ("FontAwesome2"));
			static const ImWchar icon_range2[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

			io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, sizeof(font_awesome_data), 20.f, &fontawesome2_cfg, icon_range2);

			//io.Fonts->Build();

		style.WindowPadding = { 10.f, 10.f };
		style.PopupRounding = 0.f;
		style.FramePadding = { 12.f, 6.f };
		style.ItemSpacing = { 10.f, 8.f };
		style.ItemInnerSpacing = { 6.f, 6.f };
		style.TouchExtraPadding = { 0.f, 0.f };
		style.IndentSpacing = 21.f;
		style.ScrollbarSize = 12.5f;
		style.GrabMinSize = 8.f;
		style.WindowBorderSize = 0.f;
		style.ChildBorderSize = 0.f;
		style.PopupBorderSize = 1.f;
		style.FrameBorderSize = 0.f;
		style.TabBorderSize = 0.f;
		style.WindowRounding = 0.f;
		style.ChildRounding = 0.f;
		style.FrameRounding = 0.f;
		style.ScrollbarRounding = 0.f;
		style.GrabRounding = 0.f;
		style.TabRounding = 0.f;
		style.WindowTitleAlign = { 0.5f, 0.5f };
		style.ButtonTextAlign = { 0.5f, 0.5f };
		style.DisplaySafeAreaPadding = { 3.f, 3.f };


		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImColor(0, 0, 0, 240);
		colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
		colors[ImGuiCol_Border] = ImVec4(0.30f, 0.30f, 0.30f, 0.50f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.21f, 0.21f, 0.21f, 0.54f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.21f, 0.21f, 0.21f, 0.78f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.28f, 0.27f, 0.27f, 0.54f);
		colors[ImGuiCol_TitleBg] = ImColor(6, 11, 117);
		colors[ImGuiCol_TitleBgActive] = ImColor(6, 11, 117);
		colors[ImGuiCol_TitleBgCollapsed] = ImColor(6, 11, 117, 100);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.39f, 0.38f, 0.38f, 1.00f);
		colors[ImGuiCol_Button] = ImColor(25, 25, 25);
		colors[ImGuiCol_ButtonHovered] = ImColor(33, 33, 33);
		colors[ImGuiCol_ButtonActive] = ImColor(41, 41, 41);
		colors[ImGuiCol_Header] = ImVec4(0.37f, 0.37f, 0.37f, 0.31f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.38f, 0.38f, 0.38f, 0.37f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.37f, 0.37f, 0.37f, 0.51f);
		colors[ImGuiCol_Separator] = ImVec4(0.38f, 0.38f, 0.38f, 0.50f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.46f, 0.46f, 0.46f, 0.50f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.46f, 0.46f, 0.46f, 0.64f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
		colors[ImGuiCol_Tab] = ImVec4(0.21f, 0.21f, 0.21f, 0.86f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.27f, 0.27f, 0.27f, 0.86f);
		colors[ImGuiCol_TabActive] = ImVec4(0.34f, 0.34f, 0.34f, 0.86f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.10f, 0.10f, 0.10f, 0.97f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);


		colors[ImGuiCol_ResizeGrip] = ImColor(0, 0, 0, 0);
		colors[ImGuiCol_ResizeGripHovered] = ImColor(0, 0, 0, 0);
		colors[ImGuiCol_ResizeGripActive] = ImColor(0, 0, 0, 0);

		colors[ImGuiCol_Tab] = ImVec4(ImColor(11, 26, 39));
		colors[ImGuiCol_TabHovered] = ImVec4(0.27f, 0.27f, 0.27f, 0.86f);
		colors[ImGuiCol_TabActive] = ImVec4(0.34f, 0.34f, 0.34f, 0.86f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(ImColor(11, 26, 39));
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(ImColor(11, 26, 39));





		style.Colors[ImGuiCol_ResizeGrip] = ImColor(6, 11, 117);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImColor(24, 24, 24, 200);
		style.Colors[ImGuiCol_ResizeGripActive] = ImColor(24, 24, 24, 170);
			});
	}
}