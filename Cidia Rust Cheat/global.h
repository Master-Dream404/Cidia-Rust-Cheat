#pragma once
#include <iostream>
#include <cstdarg>
#include <m_includes/XorStr/XR.hpp>
#include <vector>
#include <string>
#include <map>
#include "user.h"
namespace global
{
    inline std::string GenerateToken(int length) {
        const std::string characters = XR("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
        std::string randomString;
        randomString.reserve(length);

        // Seed the random number generator
        srand(static_cast<unsigned int>(time(nullptr)));

        for (int i = 0; i < length; ++i) {
            randomString += characters[rand() % characters.length()];
        }

        return randomString;
    }

    inline int count_time = 2000;
    inline UserImpl* m_client;
    inline bool authed = false;
    inline std::string client_token = XR("KKK_CLAN");
	inline bool debug = false;
    enum PlayerClass
    {
        player,
        friends,
        enemy,
        cheater
    };
    inline std::map<std::string, PlayerClass> PlayerClasses;


    _Check_return_opt_
        _CRT_STDIO_INLINE int print(
            _In_z_ _Printf_format_string_ const char* format,
            ...)
    {
        va_list args;
        va_start(args, format);
        int result = vprintf(format, args);
        va_end(args);

        printf(XR("\n"));

        return result;
    }

}