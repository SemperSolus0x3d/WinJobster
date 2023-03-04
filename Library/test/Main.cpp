#include <iostream>
#include <Wrappers.h>

int main()
{
    std::wstring cmdline = L"notepad.exe";

    void* handle;
    auto errCode = StartProcess(cmdline.c_str(), NULL, &handle);

    if (errCode != ErrorCode::Success)
    {
        std::wcout << L"Process start failed. Error code: " << (uint32_t)errCode << std::endl;
        std::wcin.get();
        return -1;
    }

    std::wcout << L"Is alive: " << IsAlive(handle) << std::endl;

    Kill(handle);
    std::wcout << L"Process killed" << std::endl;

    std::wcout << L"Is alive: " << IsAlive(handle) << std::endl;

    Cleanup(handle);
    return 0;
}