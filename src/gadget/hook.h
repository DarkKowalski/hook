#pragma once

#include "hook_dxgi.h"

namespace hook
{
    void Install()
    {
        hook::HookDXGI::Install();
    }

    void Uninstall()
    {
        hook::HookDXGI::Uninstall();
    }
}
