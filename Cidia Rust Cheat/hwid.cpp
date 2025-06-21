#include <iostream>
#include <comdef.h>
#include <Wbemidl.h>
#pragma comment(lib, "wbemuuid.lib")
#include "hwid.h"
#include <m_includes/XorStr/XR.hpp>
#include <atlsecurity.h> 

namespace diskuuid
{
	std::string GetDiskID() {
		ATL::CAccessToken accessToken;
		ATL::CSid currentUserSid;
		if (accessToken.GetProcessToken(TOKEN_READ | TOKEN_QUERY) &&
			accessToken.GetUser(&currentUserSid))
			return std::string(CT2A(currentUserSid.Sid()));
	}
}