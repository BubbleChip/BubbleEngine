#pragma once

#include "BEAppContextInterface.h"

class ApplicationContext : public BEAppContextInterface
{
public:
	ApplicationContext() = default;
	~ApplicationContext() = default;

	int MessageLoop() override;
};