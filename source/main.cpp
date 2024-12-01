#include <GarrysMod/Lua/Interface.h>

#include "main.h"
#include "modules/hush.h"

GMOD_MODULE_OPEN()
{
  g_Lua = LUA;

  hush::initialize();

  return 0;
}

GMOD_MODULE_CLOSE()
{
  return 0;
}