#include "hook_dxgi.h"

namespace hook
{

    HookDXGI::IDXGISwapChain4PresentType HookDXGI::RealIDXGISwapChain4Present = nullptr;

    HRESULT HookDXGI::HookIDXGISwapChain4Present(IDXGISwapChain4 *pThis, UINT SyncInterval, UINT Flags)
    {
        LOG(INFO) << "HookDXGI::HookIDXGISwapChain4Present";
        return RealIDXGISwapChain4Present(pThis, SyncInterval, Flags);
    }

    bool HookDXGI::Install()
    {
        RealIDXGISwapChain4Present = reinterpret_cast<HookDXGI::IDXGISwapChain4PresentType>(
            AddressMap::GetInstance().get_virtual_function_address(AddressMap::TargetVirtualFunction::kIDXGISwapChain4Present, L"dxgi.dll"));

        LOG(INFO) << "HookDXGI::Install";

        bool result = true;
        result &= InstallHook<HookDXGI::IDXGISwapChain4PresentType>(RealIDXGISwapChain4Present, HookIDXGISwapChain4Present, "IDXGISwapChain4::Present");

        return result;
    }

    void HookDXGI::Uninstall()
    {
        LOG(INFO) << "HookDXGI::Uninstall";

        UninstallHook<HookDXGI::IDXGISwapChain4PresentType>(RealIDXGISwapChain4Present, HookIDXGISwapChain4Present, "IDXGISwapChain4::Present");
    }

}