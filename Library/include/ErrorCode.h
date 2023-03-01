#pragma once

#include <cstdint>

enum class ErrorCode : uint32_t
{
    Success = 0,
    JobObjectCreationFailed = 1,
    CompletionPortCreationFailed = 2,
    FailedToAssociateJobWithCompletionPort = 3,
    ProcessCreationFailed = 4
};
