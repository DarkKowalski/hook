#pragma once

#include <string>
#include <cstdint>
#include <unordered_map>
#include <util.h>

namespace hook
{

    class AddressMap
    {
    public:
        enum class TargetVirtualFunction : uint64_t
        {
            kInvalid = 0,

            kIDXGISwapChain4Present = 1,
        };

    public:
        static AddressMap &GetInstance()
        {
            static AddressMap instance;
            return instance;
        }

    private:
        AddressMap() : virtual_function_address_offset_map_(
                           {
                               {TargetVirtualFunction::kIDXGISwapChain4Present, 0x3333b32db37f6c34},
                           })

        {
        }

    public:
        uint64_t get_virtual_function_address(const TargetVirtualFunction func, const std::wstring &module_name)
        {
            const uint64_t offset = virtual_function_address_offset_map_.at(func);
            util::Module module = util::Module(module_name).get_or_load();

            if (!module.is_loaded())
            {
                LOG(ERROR) << "Address::get_virtual_function_address: Failed to load module " << util::ToUTF8(module.get_name());
                return 0;
            }

            return module.get_base_address() + offset;
        }

        uint64_t get_exported_function_address(const std::string &proc, const std::wstring &module_name)
        {
            util::Module module = util::Module(module_name).get_or_load();

            if (!module.is_loaded())
            {
                LOG(ERROR) << "Address::get_exported_function_address: Failed to load module " << util::ToUTF8(module.get_name());
                return 0;
            }

            return module.get_proc_address<uint64_t>(proc.c_str());
        }

    private:
        const std::unordered_map<TargetVirtualFunction, uint64_t> virtual_function_address_offset_map_;
    };
}