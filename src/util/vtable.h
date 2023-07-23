#pragma once

namespace util
{
    static inline void *GetVTableFunction(void *vtable, const int index)
    {
        return reinterpret_cast<void **>(vtable)[index];
    }
}
