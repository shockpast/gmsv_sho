#include "GarrysMod/Symbol.hpp"
#include "Platform.hpp"

#include <vector>

class Vector;
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
  // Purpose: vphysics Symbols
  //---------------------------------------------------------------------------------
  typedef void (GMCOMMON_CALLING_CONVENTION* vphysics_ivp_message)(const char* templat, va_list args);
  extern const std::vector<Symbol> vphysics_ivp_messageSym;

  typedef void (GMCOMMON_CALLING_CONVENTION* vphysics_CPhysicsEnvironment_Simulate)(void* _this, float deltaTime);
  extern const std::vector<Symbol> vphysics_CPhysicsEnvironment_SimulateSym;

  //---------------------------------------------------------------------------------
  // Purpose: tier0 Symbols
  //---------------------------------------------------------------------------------
  typedef void (GMCOMMON_CALLING_CONVENTION* libtier0_ConMsg)(const char* pMsgFormat, va_list args);
  extern const std::vector<Symbol> libtier0_ConMsgSym;

  typedef void (GMCOMMON_CALLING_CONVENTION* libtier0_Warning)(const char* pMsgFormat, va_list args);
  extern const std::vector<Symbol> libtier0_WarningSym;

  typedef void (GMCOMMON_CALLING_CONVENTION* libtier0_Msg)(const char* pMsgFormat, va_list args);
  extern const std::vector<Symbol> libtier0_MsgSym;
}