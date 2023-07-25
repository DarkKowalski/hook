#pragma once

#include <detours/detours.h>
#include <string>

namespace hook
{
    template <typename T>
    bool InstallHook(T &real, T hook, const std::string &name)
    {
        LOG(INFO) << "InstallHook: " << name;

        LONG detours_error = DetourTransactionBegin();
        if (detours_error != NO_ERROR)
        {
            LOG(ERROR) << "InstallHook: Failed to begin DetourTransaction.";
            return false;
        }

        detours_error = DetourUpdateThread(GetCurrentThread());
        if (detours_error != NO_ERROR)
        {
            LOG(ERROR) << "InstallHook: Failed to update thread.";
            return false;
        }

        detours_error = DetourAttach(&(PVOID &)real, hook);
        if (detours_error != NO_ERROR)
        {
            LOG(ERROR) << "InstallHook: Failed to attach, error = " << detours_error;
            return false;
        }

        detours_error = DetourTransactionCommit();
        if (detours_error != NO_ERROR)
        {
            LOG(ERROR) << "InstallHook: Failed to commit DetourTransaction.";
            return false;
        }

        LOG(INFO) << "InstallHook: " << name << " success.";
        return true;
    }

    template <typename T>
    bool UninstallHook(T &real, T hook, const std::string &name)
    {
        LOG(INFO) << "UninstallHook: " << name;

        LONG detours_error = DetourTransactionBegin();
        if (detours_error != NO_ERROR)
        {
            LOG(ERROR) << "UninstallHook: Failed to begin DetourTransaction.";
            return false;
        }

        detours_error = DetourUpdateThread(GetCurrentThread());
        if (detours_error != NO_ERROR)
        {
            LOG(ERROR) << "UninstallHook: Failed to update thread.";
            return false;
        }

        detours_error = DetourDetach(&(PVOID &)real, hook);
        if (detours_error != NO_ERROR)
        {
            LOG(ERROR) << "UninstallHook: Failed to detach, error = " << detours_error;
            return false;
        }

        detours_error = DetourTransactionCommit();
        if (detours_error != NO_ERROR)
        {
            LOG(ERROR) << "UninstallHook: Failed to commit DetourTransaction.";
            return false;
        }

        LOG(INFO) << "UninstallHook: " << name << " success.";
        return true;
    }
}