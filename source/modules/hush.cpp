#include <iostream>
#include <cstdarg>
#include <stdio.h>
#include <regex>

#include <GarrysMod/Lua/LuaInterface.h>

#include "lua.h"
#include "hush.h"
#include "detour.h"
#include "main.h"

static Detouring::Hook detour_ivp_message;
void hook_ivp_message(const char* pMsgFormat, ...)
{
  if (strstr(pMsgFormat, "do_constraint_system: Couldn't invert rot matrix!"))
    return;

  va_list args;
  va_start(args, pMsgFormat);

  detour_ivp_message.GetTrampoline<symbols::vphysics_ivp_message>()(pMsgFormat, args);
}

static Detouring::Hook detour_ConMsg;
void hook_ConMsg(const char* pMsgFormat, ...)
{
  if (strstr(pMsgFormat, "Forcing client reconnect (%i)"))
    return;

  va_list args;
  va_start(args, pMsgFormat);

  char buf[4096];
  vsprintf(buf, pMsgFormat, args); // that is same logic that in libtier0.so ?

  va_end(args);

  // todo: putting just va_list seems to corrupt arguments in string...
  detour_ConMsg.GetTrampoline<symbols::libtier0_ConMsg>()(buf, args);
}

static Detouring::Hook detour_Warning;
void hook_Warning(const char* pMsgFormat, ...)
{
  if (strstr(pMsgFormat, "Bad SetLocalOrigin(%f,%f,%f) on %s"))
    return;

  if (strstr(pMsgFormat, "%s[%i]:SetAbsOrigin( %f %f %f ): Ignoring unreasonable position.")) // ? this looks messy
  {
    va_list args;
    va_start(args, pMsgFormat);

    va_arg(args, const char*);
    int entityIndex = va_arg(args, int);

    va_end(args);

    lua::PushHook("sho:SetAbsOrigin"); // todo i need something unique and good looking
    g_Lua->PushNumber(entityIndex);
    g_Lua->PCall(2, 0, true);

    return;
  }

  va_list args;
  va_start(args, pMsgFormat);

  char buf[4096];
  vsprintf(buf, pMsgFormat, args);

  va_end(args);

  detour_Warning.GetTrampoline<symbols::libtier0_Warning>()(buf, args);
}

void hook_Msg(const char* pMsgFormat, ...)
{
  if (strstr(pMsgFormat, "Weapon spawning in solid!"))
    return;

  va_list args;
  va_start(args, pMsgFormat);

  char buf[4096];
  vsprintf(buf, pMsgFormat, args);

  va_end(args);

  detour_Warning.GetTrampoline<symbols::libtier0_Msg>()(buf, args);
}

void hush::initialize()
{
  SourceSDK::ModuleLoader vphysics("vphysics");
  detour::Create(&detour_ivp_message, "ivp_message", vphysics.GetModule(), symbols::vphysics_ivp_messageSym, (void*)hook_ivp_message, 0);

  SourceSDK::ModuleLoader tier0("libtier0");
  detour::Create(&detour_ConMsg, "ConMsg", tier0.GetModule(), symbols::libtier0_ConMsgSym, (void*)hook_ConMsg, 0);
  detour::Create(&detour_Warning, "Warning", tier0.GetModule(), symbols::libtier0_WarningSym, (void*)hook_Warning, 0);

  Msg("initialized 'hush' module\n");
}