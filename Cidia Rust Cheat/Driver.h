#pragma once
#include <Windows.h>
#include <m_includes/XorStr/XR.hpp>
#include <memory>
#include <TlHelp32.h>
static std::string utf16_to_utf8(const char16_t* utf16_string) {
    std::string utf8_string;
    int i = 0;
    while (utf16_string[i] != u'\0') {
        char16_t c = utf16_string[i++];
        if (c < 0x80) {
            utf8_string += static_cast<char>(c);
        }
        else if (c < 0x800) {
            utf8_string += static_cast<char>((c >> 6) | 0xC0);
            utf8_string += static_cast<char>((c & 0x3F) | 0x80);
        }
        else {
            utf8_string += static_cast<char>((c >> 12) | 0xE0);
            utf8_string += static_cast<char>(((c >> 6) & 0x3F) | 0x80);
            utf8_string += static_cast<char>((c & 0x3F) | 0x80);
        }
    }
    return utf8_string;
}

namespace driver
{
    inline HANDLE driver_handle;
    inline DWORD pid;
    namespace codes
    {
        constexpr ULONG attach =
            CTL_CODE(FILE_DEVICE_UNKNOWN, 0x696, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
        constexpr ULONG read =
            CTL_CODE(FILE_DEVICE_UNKNOWN, 0x697, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
        constexpr ULONG write =
            CTL_CODE(FILE_DEVICE_UNKNOWN, 0x698, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
        constexpr ULONG module_address =
            CTL_CODE(FILE_DEVICE_UNKNOWN, 0x699, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
        constexpr ULONG get_pid =
            CTL_CODE(FILE_DEVICE_UNKNOWN, 0x700, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
    }
    struct Request {
        PVOID target;
        PVOID buffer;
        const char* module_name;
        PCWSTR process_name;
        PVOID base_address;
        SIZE_T size;
        SIZE_T return_size;
    };


    static bool initialize() {
        driver::driver_handle = CreateFile(XR(L"\\\\.\\yourName"), GENERIC_READ, 0, nullptr, OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL, nullptr);

        if (driver::driver_handle == INVALID_HANDLE_VALUE)
        {
            return false;
        }
        else
        {
            return true;
        }

    }

    static bool initializeBypass() {
        Request r;
        r.module_name = "yourName";
        return DeviceIoControl(driver_handle, 0x404, &r, sizeof(r), &r, sizeof(r), nullptr,
            nullptr);
    }

    inline uintptr_t get_module_base_address(const char* module_name)
    {
        Request r;
        r.module_name = module_name;
        DeviceIoControl(driver_handle, codes::module_address, &r, sizeof(r), &r, sizeof(r), nullptr, nullptr);
        return (uintptr_t)r.target;

    }
    static bool attach_to_process(PCWSTR process_name) {
        Request r;
        r.process_name = process_name;
        return DeviceIoControl(driver_handle, codes::attach, &r, sizeof(r), &r, sizeof(r), nullptr,
            nullptr);

    }

    static std::string read_unicode(const uintptr_t address, const int stringLength)
    {
        char16_t wcharTemp[128] = { '\0' };

        Request r;
        r.target = reinterpret_cast<PVOID>(address);
        r.buffer = &wcharTemp;
        r.size = stringLength * 2;

        if (!DeviceIoControl(driver_handle, codes::read, &r, sizeof(r), &r, sizeof(r), nullptr, nullptr))
            return std::string("");

        std::string u8_conv = utf16_to_utf8(wcharTemp);

        return u8_conv;
    }
    static std::string read_ascii(const uintptr_t address, const size_t size)
    {
        std::unique_ptr<char[]> buffer(new char[size]);

        Request r;
        r.target = reinterpret_cast<PVOID>(address);
        r.buffer = &buffer;
        r.size = size;
        return std::string(buffer.get());
    }

    static std::string read_bufferascii(const uintptr_t address)
    {
        char buffer[1024];

        Request r;
        r.target = reinterpret_cast<PVOID>(address);
        r.buffer = &buffer;
        r.size = 1024;
        return std::string(buffer);
    }

    template <class T>
    static T read(const std::uintptr_t addr) {
        T temp = {};

        Request r;
        r.target = reinterpret_cast<PVOID>(addr);
        r.buffer = &temp;
        r.size = sizeof(T);

        DeviceIoControl(driver_handle, codes::read, &r, sizeof(r), &r, sizeof(r), nullptr, nullptr);
        return temp;

    }

    template <class T>
    static T read_temp(const std::uintptr_t addr, size_t size) {
        T temp = {};

        Request r;
        r.target = reinterpret_cast<PVOID>(addr);
        r.buffer = &temp;
        r.size = size;

        DeviceIoControl(driver_handle, codes::read, &r, sizeof(r), &r, sizeof(r), nullptr, nullptr);
        return temp;

    }

    template <class T>
    static void read_out(const std::uintptr_t addr, T out) {

        Request r;
        r.target = reinterpret_cast<PVOID>(addr);
        r.buffer = &out;
        r.size = sizeof(T);

        DeviceIoControl(driver_handle, codes::read, &r, sizeof(r), &r, sizeof(r), nullptr, nullptr);

    }

    template <class T>
    static void write(const std::uintptr_t addr, const T& value) {
        Request r;
        r.target = reinterpret_cast<PVOID>(addr);
        r.buffer = (PVOID)&value;
        r.size = sizeof(T);

        DeviceIoControl(driver_handle, codes::write, &r, sizeof(r), &r, sizeof(r), nullptr, nullptr);
    }

    static uintptr_t GetGameAssembly() {
        return driver::get_module_base_address(XR("GameAssembly.dll"));
    }


    static uintptr_t GetUnityPlayer() {
        return driver::get_module_base_address(XR("UnityPlayer.dll"));
    }
}