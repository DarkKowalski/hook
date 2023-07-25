#include "gfx.h"

#include <util.h>

int main()
{
    util::InitLogger("devel", true);

    const uint64_t present_offset = devel::GFX::AcquireIDXGISwapChain4PresentAddressOffset();
    LOG(INFO) << "IDXGI::SwapChain4::Present address offset: 0x" << std::hex << present_offset;

    util::ShutdownLogger("devel");

    return 0;
}