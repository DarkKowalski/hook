#pragma once

namespace util
{
    static inline void *GetVTableFunctionAddress(void *class_ptr, const int index)
    {
        void **vtable = *reinterpret_cast<void ***>(class_ptr);
        return vtable[index];
    }
}
