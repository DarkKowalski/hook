#include "hook_dxgi.h"

namespace hook
{

    HookDXGI::IDXGISwapChain4PresentType HookDXGI::RealIDXGISwapChain4Present = nullptr;

    HRESULT HookDXGI::HookIDXGISwapChain4Present(IDXGISwapChain4 *pThis, UINT SyncInterval, UINT Flags)
    {
        LOG(INFO) << "HookDXGI::HookIDXGISwapChain4Present";
        return RealIDXGISwapChain4Present(pThis, SyncInterval, Flags);
    }

    bool HookDXGI::FindIDXGISwapChain4Present()
    {
        const auto dxgi_module = util::Module(L"dxgi.dll").get_or_load();
        if (!dxgi_module.is_loaded())
        {
            LOG(ERROR) << "HookDXGI::FindIDXGISwapChain4Present: Failed to load dxgi.dll";
            return false;
        }

        RealIDXGISwapChain4Present = reinterpret_cast<HookDXGI::IDXGISwapChain4PresentType>(dxgi_module.get_base_address() + 0x3333b32db37f6c34);
        return true;

        util::Window window(800, 600, L"HookDXGIWindow");
        if (window.get_handle() == nullptr)
        {
            LOG(ERROR) << "HookDXGI::FindIDXGISwapChain4Present: Failed to create window.";
            return false;
        }

        util::ComPtr<IDXGIFactory4> dxgi_factory;
        HRESULT hr = CreateDXGIFactory2(0, IID_PPV_ARGS(&dxgi_factory));
        if (FAILED(hr))
        {
            LOG(ERROR) << "HookDXGI::FindIDXGISwapChain4Present: Failed to create IDXGIFactory4.";
            return false;
        }

        util::ComPtr<IDXGISwapChain4> swap_chain4;
        {
            util::ComPtr<ID3D11Device> device;
            util::ComPtr<IDXGISwapChain> swap_chain;

            D3D_FEATURE_LEVEL feature_level = D3D_FEATURE_LEVEL_11_0;
            D3D_FEATURE_LEVEL feature_levels[] = {D3D_FEATURE_LEVEL_11_0};

            DXGI_SWAP_CHAIN_DESC swap_chain_desc = {};
            swap_chain_desc.BufferCount = 2;
            swap_chain_desc.BufferDesc.Width = 800;
            swap_chain_desc.BufferDesc.Height = 600;
            swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            swap_chain_desc.BufferDesc.RefreshRate.Numerator = 60;
            swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
            swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swap_chain_desc.OutputWindow = window.get_handle();
            swap_chain_desc.SampleDesc.Count = 1;
            swap_chain_desc.SampleDesc.Quality = 0;
            swap_chain_desc.Windowed = TRUE;
            swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
            swap_chain_desc.Flags = 0;

            hr = D3D11CreateDeviceAndSwapChain(
                nullptr,
                D3D_DRIVER_TYPE_HARDWARE,
                nullptr,
                0,
                feature_levels,
                1,
                D3D11_SDK_VERSION,
                &swap_chain_desc,
                &swap_chain,
                &device,
                &feature_level,
                nullptr);
            if (FAILED(hr))
            {
                LOG(ERROR) << "HookDXGI::FindIDXGISwapChain4Present: Failed to create D3D11 device and swap chain.";
                return false;
            }

            hr = swap_chain.As(&swap_chain4);
            if (FAILED(hr))
            {
                LOG(ERROR) << "HookDXGI::FindIDXGISwapChain4Present: Failed to get IDXGISwapChain4.";
                return false;
            }
        }

        RealIDXGISwapChain4Present = reinterpret_cast<HookDXGI::IDXGISwapChain4PresentType>(util::GetVTableFunctionAddress(swap_chain4.Get(), 8));
        if (RealIDXGISwapChain4Present == nullptr)
        {
            LOG(ERROR) << "HookDXGI::FindIDXGISwapChain4Present: Failed to get IDXGISwapChain4::Present.";
            return false;
        }

        LOG(INFO) << "HookDXGI::FindIDXGISwapChain4Present: RealIDXGISwapChain4Present = 0x" << std::hex << RealIDXGISwapChain4Present;

        const uint64_t swap_chain4_present_address = reinterpret_cast<uint64_t>(RealIDXGISwapChain4Present);
        const uint64_t dxgi_module_base_address = dxgi_module.get_base_address();
        const uint64_t diff = swap_chain4_present_address - dxgi_module_base_address;
        LOG(INFO) << "Diff = 0x" << std::hex << diff;

        return true;
    }

    bool HookDXGI::InstallIDXGISwapChain4Present()
    {
        LONG detours_error = DetourTransactionBegin();
        if (detours_error != NO_ERROR)
        {
            LOG(ERROR) << "HookDXGI::InstallIDXGISwapChain4Present: Failed to begin DetourTransaction.";
            return false;
        }

        detours_error = DetourUpdateThread(GetCurrentThread());
        if (detours_error != NO_ERROR)
        {
            LOG(ERROR) << "HookDXGI::InstallIDXGISwapChain4Present: Failed to update thread.";
            return false;
        }

        detours_error = DetourAttach(&(PVOID &)RealIDXGISwapChain4Present, HookIDXGISwapChain4Present);
        if (detours_error != NO_ERROR)
        {
            LOG(ERROR) << "HookDXGI::InstallIDXGISwapChain4Present: Failed to attach IDXGISwapChain4::Present, error = " << detours_error;
            return false;
        }

        detours_error = DetourTransactionCommit();
        if (detours_error != NO_ERROR)
        {
            LOG(ERROR) << "HookDXGI::InstallIDXGISwapChain4Present: Failed to commit DetourTransaction.";
            return false;
        }

        return true;
    }
    bool HookDXGI::Setup() {
        if (!FindIDXGISwapChain4Present())
        {
            LOG(ERROR) << "HookDXGI::Install: Failed to install IDXGISwapChain4::Present.";
            return false;
        }

        return true;
    }

    bool HookDXGI::Install()
    {
        LOG(INFO) << "HookDXGI::Install";

        if (!InstallIDXGISwapChain4Present())
        {
            LOG(ERROR) << "HookDXGI::Install: Failed to install IDXGISwapChain4::Present.";
            return false;
        }

        return true;
    }

    void HookDXGI::Uninstall()
    {
        LOG(INFO) << "HookDXGI::Uninstall";
    }

}