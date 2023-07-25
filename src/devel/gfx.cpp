#include "gfx.h"

namespace devel
{
    uint64_t GFX::AcquireIDXGISwapChain4PresentAddressOffset()
    {

        util::Module dxgi_module = util::Module(L"dxgi.dll").get_or_load();
        if (!dxgi_module.is_loaded())
        {
            LOG(ERROR) << "Cannot load dxgi.dll";
            return 0;
        }

        util::Window window(800, 600, L"GFXWindow");
        if (window.get_handle() == nullptr)
        {
            LOG(ERROR) << "Cannot create window.";
            return 0;
        }

        util::ComPtr<IDXGIFactory4> dxgi_factory;
        HRESULT hr = CreateDXGIFactory2(0, IID_PPV_ARGS(&dxgi_factory));
        if (FAILED(hr))
        {
            LOG(ERROR) << "CreateDXGIFactory2 failed, hr = 0x" << std::hex << hr;
            return 0;
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
                LOG(ERROR) << "D3D11CreateDeviceAndSwapChain failed, hr = 0x" << std::hex << hr;
                return 0;
            }

            hr = swap_chain.As(&swap_chain4);
            if (FAILED(hr))
            {
                LOG(ERROR) << "IDXGISwapChain::QueryInterface failed, hr = 0x" << std::hex << hr;
                return 0;
            }
        }

        const uint64_t present_address = reinterpret_cast<uint64_t>(util::GetVTableFunctionAddress(swap_chain4.Get(), 8));
        const uint64_t dxgi_module_base_address = dxgi_module.get_base_address();

        LOG(INFO) << "IDXGISwapChain4::Present address = 0x" << std::hex << present_address;
        LOG(INFO) << "dxgi.dll base address = 0x" << std::hex << dxgi_module_base_address;

        return present_address - dxgi_module_base_address;
    }

}