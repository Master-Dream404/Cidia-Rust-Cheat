#include <m_includes/XorStr/XR.hpp>
#include <iostream>
#include "Driver.h"
#include "global.h"
#include "kernel.h"
#include "return_spoofer.hpp"
#include "overlay.h"
#include <m_includes/filesystem/filesystem.hpp>
#include <fstream>
#include <string>
#include <m_includes/json/json.hpp>
#include <m_includes/encryption/encryption.h>
#include "auth.h"
// Function to hide console window

using json = nlohmann::json;


void hideConsoleIfNotDebug()
{
    if (!global::debug)
    {
        HWND hwnd = spoof_call(GetConsoleWindow);
        if (hwnd != nullptr)
        {
            spoof_call(ShowWindow, hwnd, SW_HIDE);
        }
    }
    std::string lr = XR("YourName");
    LPCSTR title = lr.c_str();
    spoof_call(SetConsoleTitleA, title);
}

// Function to initialize the driver
bool execute = false;
int execute_count = 0;
bool initializeDriver()
{
    auto kernel = kernel::get_current();

    while (!execute)
    {
        if (execute_count >= 10)
        {
            kernel.CMessageBox(XR("Failed to initialize driver."), XR("Cidia"), 0x00000000L);
            kernel.CExitProcess();
            return false;
        }
        if (driver::initialize())
        {
            global::print(XR("Driver was initialized"));
            return true;
        }
        Sleep(3000);
        execute_count++;
    }
    return false;
}

void initializeBypass() {
    if (driver::initializeBypass()) return;
}

//public class Player : ConsoleSystem
// Function to attach to process
bool attached = false;
int execute_count2 = 0;
bool attachToProcess()
{
    auto kernel = kernel::get_current();

    while (!attached)
    {
        if (execute_count2 >= 30)
        {
            kernel.CMessageBox(XR("You took too long to open Rust."), XR("Cidia"), 0x00000000L);
            kernel.CExitProcess();
            return false;
            break;
        }
        if (driver::attach_to_process(XR(L"RustClient.exe")))
        {
            global::print(XR("Driver was attached"));
            return true;
            break;
        }
        Sleep(3000);
        execute_count2++;
    }
    return false;
}

int main()
{
    global::debug = true;
    spoof_call(config::Login);
    if (global::authed)
    {
        if ( global::m_client->GetAuthenticate() && !global::m_client->GetUsername().empty() && !global::m_client->GetPassword().empty())
        {
            auto kernel = kernel::get_current();

            hideConsoleIfNotDebug();

            if (!initializeDriver())
            {
                global::print(XR("Driver was not initialized"));
            }
            else
            {
              
                if (!global::debug)
                {
                    HWND Rust_HWND = FindWindow(NULL, XR(L"Rust"));
                    if (Rust_HWND != NULL)
                    {
                        kernel.CMessageBox(XR("Rust was started before the bypass was loaded."), XR("Cidia"), 0x00000000L);
                        kernel.CExitProcess();
                    }

                    DWORD min_sleep_time = 10000; // 6 seconds
                    DWORD max_sleep_time = 20000; // 20 seconds
                    DWORD sleep_time_range = max_sleep_time - min_sleep_time;

                    DWORD sleep_time = (rand() % sleep_time_range) + min_sleep_time;
                    Sleep(sleep_time);
                    kernel.CMessageBox(XR("You can now start Rust."), XR("Cidia"), 0x00000000L);
               }
              
                initializeBypass();
               
                if (attachToProcess())
                {
                    global::print(XR("Driver was attached"));
                    if (!global::debug)
                    {
                        Sleep(6000);
                    }
                    overlay::Render();
                }
                else
                {
                    global::print(XR("Driver not attached"));
                }
            }
        }
        else
        {
            global::print(XR("Failed to Authenticate pocket 2"));
        }
    }
    else
    {
        global::print(XR("Failed to Authenticate"));
    }
    if (global::debug)
    {
        global::print(XR("\n\nProcess was stopped."));
        system(XR("pause"));
    }

    kernel::get_current().CExitProcess();
    return 0;
}
