#pragma once
#include <string>
#include "imgui/imgui.h"
#include <m_includes/XorStr/XR.hpp>
class HotKeys
{
public:
	std::string key_s = XR("");
	int key = 0;
	bool select_key = false;
	bool toggel = false;
};

namespace GUI
{
	void HotKey(HotKeys* key, ImVec2 size);
}