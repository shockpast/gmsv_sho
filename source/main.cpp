#include <GarrysMod/Lua/Interface.h>
#include "interfaces/interfaces.h"

#include "modules/hush.h"

GMOD_MODULE_OPEN()
{
	hush::initialize();

	return 0;
}

GMOD_MODULE_CLOSE()
{
	return 0;
}