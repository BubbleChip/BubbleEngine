#pragma once

#include "ApplicationContext/BEAppContextInterface.h"

class BEApp
{
public:
	BEApp();
	virtual ~BEApp();

	int Run();

protected:
	virtual void OnInitialize() = 0;
	virtual void OnTerminate() = 0;

private:
	BEAppContextInterface* context;
};