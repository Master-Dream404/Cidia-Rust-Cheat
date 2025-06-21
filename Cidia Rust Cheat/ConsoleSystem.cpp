#include "ConsoleSystem.h"
#include "driver.h"
#include <m_includes/XorStr/XR.hpp>
#include "global.h"
void ConsoleSystem::DisableCommand(uint64_t command)
{
	uintptr_t commandname = driver::read<uint64_t>(command + Name);

	wchar_t commandstring[36] = { '\0' };
	*commandstring = driver::read<ULONG64>((ULONG64)commandname + 0x14);

	for (std::wstring blacklistedcommand : BlacklistedCommands)
	{
		if (wcscmp(commandstring, blacklistedcommand.c_str()) == 0)
		{
			global::print(XR("[ConsoleSystem] "));
			if (global::debug)
				wprintf(commandstring);

			driver::write(command + AllowRunFromServer, false);
			global::print(XR(" - Blocked Command From Server"));
			return;
		}

	}
}
ConsoleSystem::ConsoleSystem()
{
	global::print(XR("[ConsoleSystem] Initialized"));
	uint64_t server = driver::read<uint64_t>(driver::GetGameAssembly() + Class); // Get Class Start Address
	global::print(XR("[ConsoleSystem] ConvarAdmin: 0x%llX"), server);
	this->StaticField = driver::read<uint64_t>(server + StaticField); // Set Static Padding
	global::print(XR("[ConsoleSystem] Static Fields: 0x%llX"), StaticField);
	this->AllBackingField = driver::read<uint64_t>(StaticField + AllBackingField);
	global::print(XR("[ConsoleSystem] AllBackingField: 0x%llX"), AllBackingField);
	this->ListSize = driver::read<uint32_t>(AllBackingField + ListSize);
	for (int i = 0; i < ListSize; i++)
	{
		uint64_t command = driver::read<uint64_t>(AllBackingField + (i * 0x8));
		if (command == 0x0)
			continue;
		DisableCommand(command);
	}
}