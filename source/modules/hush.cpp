#include <iostream>
#include <cstdarg>
#include <stdio.h>
#include <regex>

#include "hush.h"
#include "detour.h"

#define MAX_ERROR_BUFFER_LEN 10000 // vphysics
#define MAX_MAKE_STRING_LEN 10000 // vphysics

static Detouring::Hook detour_ivp_message;
void hook_ivp_message(const char* pMsgFormat, ...)
{
  if (strstr(pMsgFormat, "do_constraint_system: Couldn't invert rot matrix!"))
    return;

  va_list args;
  va_start(args, pMsgFormat);

  detour_ivp_message.GetTrampoline<symbols::ivp_message>()(pMsgFormat, args);
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
  detour_ConMsg.GetTrampoline<symbols::ConMsg>()(buf, args);
}

void hush::initialize()
{
  SourceSDK::ModuleLoader vphysics("vphysics");
  detour::Create(&detour_ivp_message, "ivp_message", vphysics.GetModule(), symbols::ivp_messageSym, (void*)hook_ivp_message, 0);

  SourceSDK::ModuleLoader tier0("libtier0");
  detour::Create(&detour_ConMsg, "ConMsg", tier0.GetModule(), symbols::ConMsgSym, (void*)hook_ConMsg, 0);
}