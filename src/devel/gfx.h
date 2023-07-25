#pragma once

#include <dxgi1_6.h>
#include <d3d11_1.h>

#include <util.h>
#include <cassert>

namespace devel
{
    class GFX
    {
    public:
        static uint64_t AcquireIDXGISwapChain4PresentAddressOffset();
    };
}