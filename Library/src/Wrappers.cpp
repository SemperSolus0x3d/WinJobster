﻿#include "Wrappers.h"
#include "Process.h"

WINJOBSTER_WRAPPER(ErrorCode, StartProcess)(const wchar_t* cmdline, void** handle)
{
    auto* info = new Process();

    auto errCode = info->StartProcess(cmdline);

    if (errCode != ErrorCode::Success)
    {
        Cleanup(info);
        return errCode;
    }

    *handle = info;

    return errCode;
}

WINJOBSTER_WRAPPER(bool, IsAlive)(void* handle)
{
    auto* info = reinterpret_cast<Process*>(handle);

    return info->IsAlive();
}

WINJOBSTER_WRAPPER(void, Kill)(void* handle)
{
    auto* info = reinterpret_cast<Process*>(handle);

    info->Kill();
}

WINJOBSTER_WRAPPER(void, Cleanup)(void* handle)
{
    auto* info = reinterpret_cast<Process*>(handle);

    delete info;
}
