#if defined(_WIN32)

#include "App/Platforms/Win32/ApplicationContext.h"
#include <Windows.h>

int ApplicationContext::MessageLoop()
{
	MSG msg = {};
    while (auto ret = GetMessageW(&msg, nullptr, 0, 0))  // (ret == 0 indicates "exit program".)
    {
        if (ret > 0)  // (ret > 0 indicates a message that must be processed.)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else  // (ret == -1 indicates an error.)
        {
            // Handle or log the error; possibly exit.
        }
    }

    return static_cast<int>(msg.wParam);
}

#endif