#pragma once

#include <Windows.h>
#include <DbgHelp.h>

// Write minidump on crash
namespace util
{
    static LONG WINAPI UnhandledExceptionFilter(_EXCEPTION_POINTERS *ExceptionInfo)
    {
        HANDLE file_handle = CreateFileW(L"minidump.dmp", GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (file_handle != INVALID_HANDLE_VALUE)
        {
            MINIDUMP_EXCEPTION_INFORMATION minidump_exception_information;
            minidump_exception_information.ThreadId = GetCurrentThreadId();
            minidump_exception_information.ExceptionPointers = ExceptionInfo;
            minidump_exception_information.ClientPointers = FALSE;

            MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), file_handle, MiniDumpNormal, &minidump_exception_information, nullptr, nullptr);
            CloseHandle(file_handle);
        }

        return EXCEPTION_EXECUTE_HANDLER;
    }

    static void SetupCrashHandler()
    {
        SetUnhandledExceptionFilter(UnhandledExceptionFilter);
    }

    static __forceinline void Crash()
    {
        int *p = nullptr;
        *p = 0;
    }
}