#pragma once
#include "Graphics/BEGraphicsDevice.h"

namespace BEL
{
#if defined(_WIN32)

	//Direct3D
	BEGraphicsDevice* CreateGraphicsDevice();

#endif
}