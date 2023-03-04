#pragma once

#include "Defines.h"
#include "ErrorCode.h"

WINJOBSTER_WRAPPER(ErrorCode, StartProcess)(
    const wchar_t* cmdline,
    const wchar_t* workingDir,
    void** handle
);

WINJOBSTER_WRAPPER(bool, IsAlive)(void* handle);

WINJOBSTER_WRAPPER(void, Kill)(void* handle);

WINJOBSTER_WRAPPER(void, Cleanup)(void* handle);
