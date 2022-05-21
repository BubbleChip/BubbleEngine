#include "BEApp.h"
#include "Platforms/ApplicationPlatform.h"

BEApp::BEApp()
	: context(nullptr)
{
	context = CreateApplicationContext();
}

BEApp::~BEApp()
{
	delete context;
	context = nullptr;
}

int BEApp::Run()
{
	OnInitialize();

	int exitCode = context->MessageLoop();

	OnTerminate();
	return exitCode;
}