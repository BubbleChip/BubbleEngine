#pragma once

class BEAppContextInterface
{
public:
	BEAppContextInterface() = default;
	virtual ~BEAppContextInterface() = default;

	virtual int MessageLoop() = 0;
};