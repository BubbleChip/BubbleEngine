#include "BEGraphicsDevice.h"
#include "Graphics/Platforms/GraphicsAPI.h"

BEGraphicsDevice* BEGraphicsDevice::CreateGraphicsDevice()
{
	return BEL::CreateGraphicsDevice();
}
