#pragma once

#include "App/ApplicationContext/BEAppContextInterface.h"

#include "Win32/ApplicationContext.h"

BEAppContextInterface* CreateApplicationContext()
{
	return new ApplicationContext();
}