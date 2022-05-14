#include "ApplicationContext.h"
#include <Windows.h>

int ApplicationContext::MessageLoop()
{
    //::SetUnhandledExceptionFilter(Private::ExceptionCallback);

    MSG msg = {};
    while (auto ret = GetMessageW(&msg, nullptr, 0, 0)) 
    {
        if (ret > 0) 
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else  
        {
        }
    }

    return static_cast<int>(msg.wParam);
}
