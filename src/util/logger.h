#pragma once

#ifndef GLOG_NO_ABBREVIATED_SEVERITIES
#define GLOG_NO_ABBREVIATED_SEVERITIES
#endif

#include <glog/logging.h>

#include <string>

#include <windows.h>

namespace util
{
    static void InitLogger(const std::string &module_name, const bool flush_immediately)
    {
        const DWORD thread_id = GetCurrentThreadId();
        const DWORD process_id = GetCurrentProcessId();

        if (google::IsGoogleLoggingInitialized())
        {
            LOG(INFO) << module_name << "(" << process_id << ":" << thread_id << ")"
                      << " tried to initialize logger twice.";
            return;
        }

        FLAGS_log_dir = "./log";
        CreateDirectoryA(FLAGS_log_dir.c_str(), NULL);
        FLAGS_alsologtostderr = true;
        FLAGS_logbufsecs = flush_immediately ? 0 : 30;
        google::InitGoogleLogging(module_name.c_str());

        LOG(INFO) << "Logger was initialized by " << module_name << "(" << process_id << ":" << thread_id << ").";
    }

    static void ShutdownLogger(const std::string &module_name)
    {
        const DWORD thread_id = GetCurrentThreadId();
        const DWORD process_id = GetCurrentProcessId();

        if (!google::IsGoogleLoggingInitialized())
        {
            LOG(INFO) << module_name << "(" << process_id << ":" << thread_id << ")"
                      << " tried to shutdown logger twice.";

            return;
        }

        LOG(INFO) << "Logger is being shutdown by " << module_name << "(" << process_id << ":" << thread_id << ").";
        google::ShutdownGoogleLogging();
    }
}
