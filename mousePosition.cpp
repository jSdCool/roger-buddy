#include "mousePosition.hpp"

#ifdef _WIN32
#include <windows.h>
#elif defined(__APPLE__)
#include <ApplicationServices/ApplicationServices.h>
#else
//requires linking against libX11
#include <X11/Xlib.h>//prbly wont work on wayland :(
#endif


myVector getScreenMousePosition() {
#ifdef _WIN32
    POINT cursorPos;
    GetCursorPos(&cursorPos); // Native Windows API
    return {static_cast<float>(cursorPos.x),static_cast<float>(cursorPos.y)};
#elif defined(__APPLE__)
    //I do not own a mac. this prbly works
    CGEventRef event = CGEventCreate(NULL);
    CGPoint cursor = CGEventGetLocation(event);
    CFRelease(event);
    return { static_cast<float>(cursor.x), static_cast<float>(cursor.y) };
#else
    //having linker issues, not going to bother checking if it actualy works
    Display *display = XOpenDisplay(NULL);
    Window root = DefaultRootWindow(display);
    Window child;
    int rootX, rootY, winX, winY;
    unsigned int mask;

    XQueryPointer(display, root, &root, &child, &rootX, &rootY, &winX, &winY, &mask);
    XCloseDisplay(display);

    return { static_cast<float>(rootX), static_cast<float>(rootY) };
#endif
}