#pragma once

#ifdef WINJOBSTER_EXPORT
    #define WINJOBSTER_INTERFACE __declspec(dllexport)
#else
    #define WINJOBSTER_INTERFACE __declspec(dllimport)
#endif

#define WINJOBSTER_CONV __stdcall

#define WINJOBSTER_WRAPPER(returnType, name) \
    extern "C" WINJOBSTER_INTERFACE returnType WINJOBSTER_CONV name
