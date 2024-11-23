#include "../symbols.h"

#include <iostream>
#include <cstdarg>
#include <basetypes.h>

#define MAX_ERROR_BUFFER_LEN 10000 // vphysics
#define MAX_MAKE_STRING_LEN 10000 // vphysics

namespace hush
{
	void ivp_message(const char* templat, ...);

	void initialize();
}