#pragma once
#include "BEAppContextInterface.h"
//#include "Win32/ApplicationContext.h"
#include "ApplicationContext.h"


BEAppContextInterface* CreateApplicationContext()
{
	return new ApplicationContext();
}