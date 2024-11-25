#include "GarrysMod/Symbol.hpp"
#include "Platform.hpp"

#include <vector>

class Color;

#if defined SYSTEM_WINDOWS
#if defined ARCHITECTURE_X86_64
#define GMCOMMON_CALLING_CONVENTION __fastcall
#else
#define GMCOMMON_CALLING_CONVENTION __thiscall
#endif
#else
#define GMCOMMON_CALLING_CONVENTION
#endif

namespace symbols
{
  //---------------------------------------------------------------------------------
  // Purpose: "hush" Symbols
  //---------------------------------------------------------------------------------
  typedef void (GMCOMMON_CALLING_CONVENTION* ivp_message)(const char* templat, ...);
  extern const std::vector<Symbol> ivp_messageSym;
}