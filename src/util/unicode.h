#pragma once

#include <codecvt>
#include <locale>
#include <string>

namespace util
{

    static inline std::wstring ToUTF16(const std::string &utf8)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        return converter.from_bytes(utf8);
    }

    static inline std::string ToUTF8(const std::wstring &utf16)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        return converter.to_bytes(utf16);
    }
}