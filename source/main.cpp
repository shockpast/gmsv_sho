#include <GarrysMod/Lua/Interface.h>

#include "modules/hush.h"
#include "modules/vphysics.h"
#include "main.h"

GMOD_MODULE_OPEN()
{
  g_Lua = LUA;

  hush::initialize();
  vphysics::initialize();

  return 0;
}

GMOD_MODULE_CLOSE()
{
  return 0;
}