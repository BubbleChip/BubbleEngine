#include "BEGraphicsDevice.h"
#include "Graphics/Platforms/GraphicsAPI.h"
#include <fstream>

BEGraphicsDevice* BEGraphicsDevice::CreateGraphicsDevice()
{
	return BEL::CreateGraphicsDevice();
}

BEObject<BEShader> BEGraphicsDevice::CreateShader(const std::wstring path, const std::string& entry, BEShader::StageType stage)
{
	BEObject<BEShader> result = nullptr;

	std::ifstream file(path.data(), std::ios::in | std::ios::binary | std::ios::ate);
	if (file.is_open())
	{
		std::streampos size = file.tellg();
		char* code = new char[size];

		file.seekg(0, std::ios::beg);
		file.read(code, size);

		// char* -> vector<uint8_t> :: use std::span :: c++20 up
		result = CreateShader(std::vector<uint8_t>(code, code + size), entry, stage);

		delete[] code;
		file.close();
	}

	return result;
}
