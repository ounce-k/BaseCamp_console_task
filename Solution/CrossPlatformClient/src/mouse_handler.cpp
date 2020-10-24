#if defined (WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <windows.h>
#elif __linux
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include "mouse_handler.h"

bool GetCoordAndClicks(MyPoint& output_p, char& key)
{
#if defined (WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    POINT p;
    if (GetCursorPos(&p) == 0)
    {
        return false;
    }
    output_p.x = p.x;
    output_p.y = p.y;
    key = 0;
    if ((GetKeyState(VK_LBUTTON) & 0x80) != 0)
    {
        key = 1;
        printf("LBUTTON is pressed \n");
    }
    if ((GetKeyState(VK_RBUTTON) & 0x80) != 0)
    {
        key = 2;
        printf("RBUTTON is pressed \n");
    }
#elif __linux
    Window root_window;
    int root_x, root_y;
    unsigned int mask;
    int win_x, win_y;
    Display* display = XOpenDisplay(NULL);
    XQueryPointer(display, DefaultRootWindow(display), &root_window, &root_window, &root_x, &root_y, &win_x, &win_y, &mask);
    output_p.x = root_x;
    output_p.y = root_y;
    if (mask == 0)
    {
        key = 0;
    }
    else if (mask == 256)
    {
        key = 1;
    }
    else if (mask == 1024)
    {
        key = 2;
    }
    XCloseDisplay(display);
#endif
    return true;
}