#pragma once

#include "hook_dxgi.h"

namespace hook
{
    void Setup()
    {
        hook::HookDXGI::Setup();
        hook::HookDXGI::Install();
    }

    void Install()
    {
        hook::HookDXGI::Install();
    }
}
