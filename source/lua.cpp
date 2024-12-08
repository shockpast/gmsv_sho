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

void lua::ThrowError(const char* error, ...)
{
  char buf[1024];

  va_list args;
  va_start(args, error);

  vsnprintf(buf, sizeof(buf), error, args);
  g_Lua->ThrowError(buf);

  va_end(args);
}

void lua::StartTable()
{
  g_Lua->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
  g_Lua->CreateTable();
}

void lua::AddFunction(GarrysMod::Lua::CFunc func, const char* name)
{
  g_Lua->PushString(name);
  g_Lua->PushCFunction(func);
  g_Lua->RawSet(-3);
}

void lua::FinishTable(const char* name)
{
  g_Lua->SetField(-2, name);
  g_Lua->Pop();
}