#pragma once

#include <string>
#include <Windows.h>

#include "ErrorCode.h"

class Process
{
public:
    Process();
    ~Process();

    ErrorCode StartProcess(const std::wstring cmdline);

    bool IsAlive();
    void Kill();
private:
    STARTUPINFOW m_StartupInfo;
    PROCESS_INFORMATION m_ProcessInfo;
    HANDLE m_Job = INVALID_HANDLE_VALUE;
    HANDLE m_CompletionPort = INVALID_HANDLE_VALUE;
    std::wstring m_Cmdline;
    bool m_IsAlive = true;
};
