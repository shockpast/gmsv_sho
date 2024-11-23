#include <iostream>
#include <cstdarg>
#include <basetypes.h>
#include <stdio.h>
#include <regex>

#include "hush.h"
#include "../symbols.h"
#include "detour.h"

#define MAX_ERROR_BUFFER_LEN 10000 // vphysics
#define MAX_MAKE_STRING_LEN 10000 // vphysics

static Detouring::Hook detour_ivp_message;
void hush::ivp_message(const char* templat, ...)
{
	if (strstr(templat, "do_constraint_system: Couldn't invert rot matrix!"))
		return;

	// making args.. yada yada yada
	//
	// not sure that all of below is needed
	// most likely this can be simplified
	char buffer[MAX_ERROR_BUFFER_LEN];
	char* p = buffer;

	memset(buffer, 0, MIN(1000, MAX_ERROR_BUFFER_LEN));
	sprintf(buffer, "ERROR: ");
	p += strlen(buffer);

	va_list args;
	va_start(args, templat);
	vsnprintf(buffer, MAX_MAKE_STRING_LEN, templat, args);
	va_end(args);

	//
	detour_ivp_message.GetTrampoline<symbols::ivp_message>()(buffer, args);
}

void hush::initialize()
{
#if SYSTEM_IS_LINUX
	// they are not '_srv' suffixed on x64, strange
	SourceSDK::ModuleLoader vphysics("vphysics");
#else
	SourceSDK::ModuleLoader vphysics("vphysics");
#endif

	detour::Create(&detour_ivp_message, "ivp_message", vphysics.GetModule(), symbols::ivp_messageSym, (void*)hush::ivp_message, 0);
}