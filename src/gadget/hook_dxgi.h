#pragma once

#include <windows.h>

#include <combaseapi.h>
#include <dxgi1_6.h>
#include <d3d11.h>

#include <detours/detours.h>
#include <util.h>

namespace hook
{
    class HookDXGI
    {
    public:
        using IDXGISwapChain4PresentType = HRESULT(__stdcall *)(IDXGISwapChain4 *pThis, UINT SyncInterval, UINT Flags);

    public:
        static HRESULT __stdcall HookIDXGISwapChain4Present(IDXGISwapChain4 *pThis, UINT SyncInterval, UINT Flags);
        static bool FindIDXGISwapChain4Present();
        static bool InstallIDXGISwapChain4Present();

    public:
        static bool Setup();
        static bool Install();
        static void Uninstall();

    public:
        static IDXGISwapChain4PresentType RealIDXGISwapChain4Present;
    };

}; // namespace hook