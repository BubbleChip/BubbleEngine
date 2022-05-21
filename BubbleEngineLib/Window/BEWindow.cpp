#include "BEWindow.h"
#include "WindowPlatform/WindowPlatform.h"

BEWindow* BEWindow::CreatePlatformWindow()
{
    return BEL::CreatePlatformWindow();
}
