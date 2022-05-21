#pragma once

#if defined(_WIN32)

#include "BECore/BEInclude.h"
#include "App/ApplicationContext/BEAppContextInterface.h"

class ApplicationContext : public BEAppContextInterface
{
public:
	int MessageLoop() override;
};

#endif