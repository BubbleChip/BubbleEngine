#include "Window.h"

namespace BEL
{
    BEWindow* CreatePlatformWindow()
    {
        return new Window();
    }
}

Window::Window()
	: handle(nullptr),
	width(0),
	height(0)
{
}

void Window::Create()
{
    // Initialize the window class.
    WNDCLASSEXW windowClass = { 0 };
    windowClass.cbSize = sizeof(windowClass);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = ::GetModuleHandleW(NULL);
    windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.lpszClassName = L"BEWindowClass";
    ::RegisterClassExW(&windowClass);

    handle = ::CreateWindowExW(0, L"BEWindowClass", L"BubbleEngine",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        nullptr, nullptr, ::GetModuleHandleW(NULL), nullptr);
    BEASSERT_DEBUG(handle);

    ::SetLastError(0);
    if (!::SetWindowLongPtrW(handle, GWLP_USERDATA, (LONG_PTR)this))
    {
        BEASSERT_DEBUG(::GetLastError() == 0);
    }
}

void Window::Destroy()
{
    BEASSERT_DEBUG(handle);
    ::PostMessageW(handle, WM_CLOSE, 0, 0);
    handle = NULL;
}

void Window::Show()
{
    BEASSERT_DEBUG(handle);
    ::ShowWindow(handle, SW_SHOWNORMAL);
}

void Window::Hide()
{
    BEASSERT_DEBUG(handle);
    ::ShowWindow(handle, SW_HIDE);
}

float Window::AspectRatio() const
{
    return static_cast<float>(width) / static_cast<float>(height);
}

void* Window::PlatformHandle() const
{
    BEASSERT_DEBUG(handle);
    return handle;
}

LRESULT Window::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    Window* window = (Window*)::GetWindowLongPtrW(hWnd, GWLP_USERDATA);
    if (window)
    {
        switch (uMsg)
        {
        case WM_SIZE:
        {
            uint32_t width = LOWORD(lParam);
            uint32_t height = HIWORD(lParam);
            if (window->width != width || window->height != height)
            {
                window->width = width;
                window->height = height;
            }
            return 0;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }
    }

    return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
}
