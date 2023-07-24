#pragma once

#include <Windows.h>

#include <string>
#include <cstdint>

#include <logger.h>

namespace util
{

    class Window
    {
    public:
        Window(const uint32_t width, const uint32_t height, const std::wstring &title) : window_title_(title)
        {
            window_handle_ = CreateWindowEx(0, L"Static", title.c_str(), WS_POPUP,
                                            0, 0, 2, 2, nullptr, nullptr, nullptr, nullptr);
        }

        ~Window()
        {
            if (window_handle_ != nullptr)
            {
                DestroyWindow(window_handle_);
                window_handle_ = nullptr;
            }
        }

    public:
        HWND get_handle() const
        {
            return window_handle_;
        }

    private:
        HWND window_handle_ = nullptr;
        const std::wstring window_title_;
    };
}