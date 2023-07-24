#pragma once

#include <Windows.h>
#include <string>

#include "logger.h"
#include "unicode.h"

namespace util
{
    class Module
    {
    public:
        Module(const std::wstring &name) : module_name_(name)
        {
        }

    public:
        Module &get_or_load()
        {
            if (module_handle_ == nullptr)
            {
                module_handle_ = GetModuleHandleW(module_name_.c_str());
                if (module_handle_ == nullptr)
                {
                    module_handle_ = LoadLibraryW(module_name_.c_str());
                    if (module_handle_ == nullptr)
                    {
                        LOG(ERROR) << "Module::GetOrLoad: Failed to load module " << ToUTF8(module_name_);
                    }
                }
            }
            return *this;
        }

        void unload()
        {
            if (module_handle_ != nullptr)
            {
                if (!FreeLibrary(module_handle_))
                {
                    LOG(ERROR) << "Module::Unload: Failed to unload module " << ToUTF8(module_name_);
                    return;
                }
                module_handle_ = nullptr;
            }
        }

        bool is_loaded() const
        {
            return module_handle_ != nullptr;
        }

        template <typename T>
        T get_proc_address(const char *proc_name)
        {
            return reinterpret_cast<T>(::GetProcAddress(module_handle_, proc_name));
        }

        HMODULE get_handle() const
        {
            return module_handle_;
        }

        const std::wstring &get_name() const
        {
            return module_name_;
        }

        const uint64_t get_base_address() const
        {
            return reinterpret_cast<uint64_t>(module_handle_);
        }

    private:
        HMODULE module_handle_;
        const std::wstring module_name_;
    };

}