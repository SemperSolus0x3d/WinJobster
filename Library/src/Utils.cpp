#include <utility>
#include "Utils.h"

void SafeCloseHandle(HANDLE& handle)
{
    if (handle != INVALID_HANDLE_VALUE)
        CloseHandle(std::exchange(handle, INVALID_HANDLE_VALUE));
}
