#include "main.hpp"
#ifdef _WIN32
#include <windows.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>

void TryAttachConsole() {
    // Attempt to attach to the parent process's console
    // By default a "GUI" application does not have std out
    if (AttachConsole(ATTACH_PARENT_PROCESS)) {
        // Redirect standard streams to the attached console
        FILE* fp;
        freopen_s(&fp, "CONOUT$", "w", stdout);
        freopen_s(&fp, "CONOUT$", "w", stderr);
        freopen_s(&fp, "CONIN$", "r", stdin);

        // Optional: Sync C++ cin/cout with the new file pointers
        std::ios::sync_with_stdio();
    }
}
//for a windows application to launch in "GUI" mode it needs to define a WinMain entry point ionstead of main
//I have no idea what these parameters are
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, PSTR szCmdLine, int sw) {
    TryAttachConsole();//still give std out if possible
    return main(); // Uses MSVC-specific globals to call your standard main
}
#endif