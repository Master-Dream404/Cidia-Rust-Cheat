#include "Hotkey.h"
#include "imgui/imgui.h"
#include <imgui/imgui_internal.h>
#include <Windows.h>
#include <map>
#include <m_includes/XorStr/XR.hpp>

std::map<std::string, int> keys = {
    {"Backspace", VK_BACK},
    {"Tab", VK_TAB},
    {"Enter", VK_RETURN},
    {"Shift", VK_SHIFT},
    {"Control", VK_CONTROL},
    {"Alt", VK_MENU},
    {"Pause", VK_PAUSE},
    {"Caps Lock", VK_CAPITAL},
    {"Escape", VK_ESCAPE},
    {"Space", VK_SPACE},
    {"Page Up", VK_PRIOR},
    {"Page Down", VK_NEXT},
    {"End", VK_END},
    {"Home", VK_HOME},
    {"Left Arrow", VK_LEFT},
    {"Up Arrow", VK_UP},
    {"Right Arrow", VK_RIGHT},
    {"Down Arrow", VK_DOWN},
    {"Select", VK_SELECT},
    {"Print", VK_PRINT},
    {"Execute", VK_EXECUTE},
    {"Print Screen", VK_SNAPSHOT},
    {"Insert", VK_INSERT},
    {"Delete", VK_DELETE},
    {"Help", VK_HELP},
    {"Left Windows", VK_LWIN},
    {"Right Windows", VK_RWIN},
    {"Apps", VK_APPS},
    {"Sleep", VK_SLEEP},
    {"Numpad 0", VK_NUMPAD0},
    {"Numpad 1", VK_NUMPAD1},
    {"Numpad 2", VK_NUMPAD2},
    {"Numpad 3", VK_NUMPAD3},
    {"Numpad 4", VK_NUMPAD4},
    {"Numpad 5", VK_NUMPAD5},
    {"Numpad 6", VK_NUMPAD6},
    {"Numpad 7", VK_NUMPAD7},
    {"Numpad 8", VK_NUMPAD8},
    {"Numpad 9", VK_NUMPAD9},
    {"Multiply", VK_MULTIPLY},
    {"Add", VK_ADD},
    {"Separator", VK_SEPARATOR},
    {"Subtract", VK_SUBTRACT},
    {"Decimal", VK_DECIMAL},
    {"Divide", VK_DIVIDE},
    {"F1", VK_F1},
    {"F2", VK_F2},
    {"F3", VK_F3},
    {"F4", VK_F4},
    {"F5", VK_F5},
    {"F6", VK_F6},
    {"F7", VK_F7},
    {"F8", VK_F8},
    {"F9", VK_F9},
    {"F10", VK_F10},
    {"F11", VK_F11},
    {"F12", VK_F12},
    {"Num Lock", VK_NUMLOCK},
    {"Scroll Lock", VK_SCROLL},
    {"Left Shift", VK_LSHIFT},
    {"Right Shift", VK_RSHIFT},
    {"Left Control", VK_LCONTROL},
    {"Right Control", VK_RCONTROL},
    {"Left Alt", VK_LMENU},
    {"Right Alt", VK_RMENU},
    {"Browser Back", VK_BROWSER_BACK},
    {"Browser Forward", VK_BROWSER_FORWARD},
    {"Browser Refresh", VK_BROWSER_REFRESH},
    {"Browser Stop", VK_BROWSER_STOP},
    {"Browser Search", VK_BROWSER_SEARCH},
    {"Browser Favorites", VK_BROWSER_FAVORITES},
    {"Browser Home", VK_BROWSER_HOME},
    {"Volume Mute", VK_VOLUME_MUTE},
    {"Volume Down", VK_VOLUME_DOWN},
    {"Volume Up", VK_VOLUME_UP},
    {"Media Next Track", VK_MEDIA_NEXT_TRACK},
    {"Media Previous Track", VK_MEDIA_PREV_TRACK},
    {"Media Stop", VK_MEDIA_STOP},
    {"Media Play/Pause", VK_MEDIA_PLAY_PAUSE},
    {"Launch Mail", VK_LAUNCH_MAIL},
    {"Launch Media Select", VK_LAUNCH_MEDIA_SELECT},
    {"Launch App1", VK_LAUNCH_APP1},
    {"Launch App2", VK_LAUNCH_APP2},
    {";", VK_OEM_1}, // ';:' for US
    {"+", VK_OEM_PLUS}, // '+' any country
    {",", VK_OEM_COMMA}, // ',' any country
    {"-", VK_OEM_MINUS}, // '-' any country
    {".", VK_OEM_PERIOD}, // '.' any country
    {"/", VK_OEM_2}, // '/?' for US
    {"`", VK_OEM_3}, // '`~' for US
    {"[", VK_OEM_4}, // '[{' for US
    {"\\", VK_OEM_5}, // '\|' for US
    {"]", VK_OEM_6}, // ']}' for US
    {"'", VK_OEM_7}, // ''"' for US
    {"OEM_8", VK_OEM_8},
    {"OEM_AX", VK_OEM_AX}, // 'AX' key on Japanese AX kbd
    {"OEM_102", VK_OEM_102}, // "<>" or "\|" on RT 102-key kbd.
    {"ICO Help", VK_ICO_HELP}, // Help key on ICO
    {"ICO 00", VK_ICO_00}, // 00 key on ICO
    {"Process Key", VK_PROCESSKEY},
    {"ICO Clear", VK_ICO_CLEAR},
    {"Packet", VK_PACKET},
    {"Attn", VK_ATTN}, // Attn key
    {"CrSel", VK_CRSEL}, // CrSel key
    {"ExSel", VK_EXSEL}, // ExSel key
    {"Erase EOF", VK_EREOF}, // Erase EOF key
    {"Play", VK_PLAY}, // Play key
    {"Zoom", VK_ZOOM}, // Zoom key
    {"No Name", VK_NONAME}, // Reserved
    {"PA1", VK_PA1}, // PA1 key
    {"Clear", VK_OEM_CLEAR}, // Clear key
    //{"A", 0x41}, // A key
    {"B", 0x42}, // B key
    {"C", 0x43}, // C key
    //{"D", 0x44}, // D key
    {"E", 0x45}, // E key
    {"F", 0x46}, // F key
    {"G", 0x47}, // G key
    {"H", 0x48}, // H key
    {"I", 0x49}, // I key
    {"J", 0x4A}, // J key
    {"K", 0x4B}, // K key
    {"L", 0x4C}, // L key
    {"M", 0x4D}, // M key
    {"N", 0x4E}, // N key
    {"O", 0x4F}, // O key
    {"P", 0x50}, // P key
    {"Q", 0x51}, // Q key
    {"R", 0x52}, // R key
    //{"S", 0x53}, // S key
    {"T", 0x54}, // T key
    {"U", 0x55}, // U key
    {"V", 0x56}, // V key
   // {"W", 0x57}, // W key
    {"X", 0x58}, // X key
    {"Y", 0x59}, // Y key
    {"Z", 0x5A}, // Z key
    {"Left Mouse", VK_LBUTTON}, // Left mouse button
    {"Right Mouse", VK_RBUTTON}, // Right mouse button
    {"Middle Mouse", VK_MBUTTON}, // Middle mouse button
    {"X1 Mouse", VK_XBUTTON1}, // X1 mouse button
    {"X2 Mouse", VK_XBUTTON2} // X2 mouse button
};


namespace GUI
{
    void HotKey(HotKeys* key, ImVec2 size) {
        if (!key->select_key)
        {
            if (ImGui::Button(key->key_s.c_str(), size))
            {
                key->select_key = true;
            }
        }
        if (key->select_key)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetColorU32(ImGuiCol_ButtonActive));
            ImGui::Button(XR("..."), size);
            ImGui::PopStyleColor();

            for (auto& pin : keys)
            {
                if (GetAsyncKeyState(pin.second) & 0x8000)
                {
                    key->key_s = pin.first;
                    key->key = pin.second;
                    key->select_key = false;
                }
            }
        }
    }
}
