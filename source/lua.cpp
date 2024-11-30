#include <GarrysMod/Lua/LuaInterface.h>

#include "lua.h"
#include "main.h"

void lua::PushHook(const char* name)
{
  g_Lua->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
  g_Lua->GetField(-1, "hook");
  g_Lua->GetField(-1, "Run");
  int reference = g_Lua->ReferenceCreate();
  g_Lua->Pop(2);
  g_Lua->ReferencePush(reference);
  g_Lua->ReferenceFree(reference);
  g_Lua->PushString(name);
}