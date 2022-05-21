#pragma once

#include "Window/BEWindow.h"
#include "BECore/BEInclude.h"
#include <Windows.h>

class Window : public BEWindow
{
public:
	Window();
	~Window() = default;

	void Create() override;
	void Destroy() override;

	void Show() override;
	void Hide() override;

	virtual uint32_t Width() const override { return width; }
	virtual uint32_t Height() const override { return height; }
	virtual float AspectRatio() const override;

	virtual void* PlatformHandle() const override;

protected:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	HWND handle;

	uint32_t width;
	uint32_t height;
};