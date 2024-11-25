#include <iostream>
#include <cstdarg>
#include <stdio.h>
#include <regex>

#include "hush.h"
#include "detour.h"

#define MAX_ERROR_BUFFER_LEN 10000 // vphysics
#define MAX_MAKE_STRING_LEN 10000 // vphysics

static Detouring::Hook detour_ivp_message;
void hush::ivp_message(const char* templat, ...)
{
  if (strstr(templat, "do_constraint_system: Couldn't invert rot matrix!"))
    return;

  va_list args;
  va_start(args, templat);

  detour_ivp_message.GetTrampoline<symbols::ivp_message>()(templat, args);
}

void hush::initialize()
{
  SourceSDK::ModuleLoader vphysics("vphysics");

  detour::Create(&detour_ivp_message, "ivp_message", vphysics.GetModule(), symbols::ivp_messageSym, (void*)hush::ivp_message, 0);
}