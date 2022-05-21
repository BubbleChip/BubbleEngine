#pragma once
#include "BECore/BEInclude.h"
#include "BECore/BERefCounter.h"

class BEL_API BEWindow : public BERefCounter
{
public:
	virtual ~BEWindow() = default;

	virtual void Create() = 0;
	virtual void Destroy() = 0;

	virtual void Show() = 0;
	virtual void Hide() = 0;

	virtual uint32_t Width() const = 0;
	virtual uint32_t Height() const = 0;
	virtual float AspectRatio() const = 0;

	virtual void* PlatformHandle() const = 0;
	
	static BEWindow* CreatePlatformWindow();

protected:
	BEWindow() = default;
};