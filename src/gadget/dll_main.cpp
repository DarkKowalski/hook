#include <windows.h>
#include <detours/detours.h>
#include <util.h>

#include "hook.h"

BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved)
{
    LONG error;
    (void)hinst;
    (void)reserved;

    if (DetourIsHelperProcess())
    {
        return TRUE;
    }

    if (dwReason == DLL_PROCESS_ATTACH)
    {
        DetourRestoreAfterWith();

        util::SetupCrashHandler();

        util::InitLogger("gadget", true);

        // New Thread for Detouring
        // const auto detour_thread = CreateThread(
        //     nullptr,
        //     0,
        //     reinterpret_cast<LPTHREAD_START_ROUTINE>(hook::Setup),
        //     nullptr,
        //     0,
        //     nullptr);
        // SetThreadDescription(detour_thread, L"SetupThread");

        hook::Setup();

        LOG(INFO) << "gadget.dll: Starting.";
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        LOG(INFO) << "gadget.dll: Exiting.";
        util::ShutdownLogger("gadget");
    }
    return TRUE;
}
