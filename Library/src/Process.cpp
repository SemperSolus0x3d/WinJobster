﻿#include "Process.h"
#include "Utils.h"

const ULONG_PTR CompletionKey = 52534;

Process::Process()
{
    ZeroMemory(&m_ProcessInfo, sizeof(m_ProcessInfo));

    m_ProcessInfo.hProcess =
        m_ProcessInfo.hThread = INVALID_HANDLE_VALUE;

    ZeroMemory(&m_StartupInfo, sizeof(m_StartupInfo));

    m_StartupInfo.cb = sizeof(m_StartupInfo);

    m_StartupInfo.hStdOutput =
        m_StartupInfo.hStdError =
        m_StartupInfo.hStdInput = INVALID_HANDLE_VALUE;
}

Process::~Process()
{
    SafeCloseHandle(m_ProcessInfo.hProcess);
    SafeCloseHandle(m_ProcessInfo.hThread);
    SafeCloseHandle(m_Job);
    SafeCloseHandle(m_CompletionPort);
}

ErrorCode Process::StartProcess(const std::wstring cmdline)
{
    m_Cmdline = cmdline;

    m_Job = CreateJobObjectW(NULL, NULL);

    if (m_Job == INVALID_HANDLE_VALUE)
        return ErrorCode::JobObjectCreationFailed;

    m_CompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

    if (m_CompletionPort == NULL)
        return ErrorCode::CompletionPortCreationFailed;

    JOBOBJECT_ASSOCIATE_COMPLETION_PORT info;
    info.CompletionKey = (PVOID)CompletionKey;
    info.CompletionPort = m_CompletionPort;

    if (!SetInformationJobObject(
        m_Job,
        JobObjectAssociateCompletionPortInformation,
        &info,
        sizeof(info))
    )
        return ErrorCode::FailedToAssociateJobWithCompletionPort;

    if (!CreateProcessW(
        NULL,
        &m_Cmdline[0],
        NULL,
        NULL,
        TRUE,
        CREATE_SUSPENDED,
        NULL,
        NULL,
        &m_StartupInfo,
        &m_ProcessInfo
    ))
        return ErrorCode::ProcessCreationFailed;

    AssignProcessToJobObject(m_Job, m_ProcessInfo.hProcess);

    ResumeThread(m_ProcessInfo.hThread);

    return ErrorCode::Success;
}

bool Process::IsAlive()
{
    if (!m_IsAlive)
        return false;

    DWORD completionCode;
    ULONG_PTR completionKey;
    LPOVERLAPPED overlapped;

    if (!GetQueuedCompletionStatus(
        m_CompletionPort,
        &completionCode,
        &completionKey,
        &overlapped,
        0
    ))
    {
        if (overlapped == NULL)
            return true;

        m_IsAlive = false;
        return false;
    }

    if (completionKey == CompletionKey && 
        completionCode == JOB_OBJECT_MSG_ACTIVE_PROCESS_ZERO)
    {
        m_IsAlive = false;
        return false;
    }

    return true;
}

void Process::Kill()
{
    auto retValue = TerminateJobObject(m_Job, 0);
    m_IsAlive = false;
}
