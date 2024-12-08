#include "symbols.h"

static Symbol NULL_SYMBOL = Symbol::FromSignature("");

namespace symbols
{
  //---------------------------------------------------------------------------------
  // Purpose: vphysics Symbols
  //---------------------------------------------------------------------------------
  const std::vector<Symbol> vphysics_ivp_messageSym = {
    // not sure
    Symbol::FromName("_Z11ivp_messagePKcz"),
    // 55 48 89 E5 41 54 53 48 81 EC ? ? ? ? 84 C0 48 89 B5 ? ? ? ? 48 89 95 ? ? ? ? 48 89 8D ? ? ? ? 4C 89 85 ? ? ? ? 4C 89 8D ? ? ? ? 74 ? 0F 29 85 ? ? ? ? 0F 29 4D ? 0F 29 55 ? 0F 29 5D ? 0F 29 65 ? 0F 29 6D ? 0F 29 75 ? 0F 29 7D ? 48 8D 9D ? ? ? ? 31 F6 49 89 FC 64 48 8B 04 25 ? ? ? ? 48 89 85 ? ? ? ? 31 C0 BA ? ? ? ? 48 89 DF E8 ? ? ? ? 4C 8D 8D
    Symbol::FromSignature("\x55\x48\x89\xE5\x41\x54\x53\x48\x81\xEC****\x84\xC0\x48\x89\xB5****\x48\x89\x95****\x48\x89\x8D****\x4C\x89\x85****\x4C\x89\x8D****\x74*\x0F\x29\x85****\x0F\x29\x4D*\x0F\x29\x55*\x0F\x29\x5D*\x0F\x29\x65*\x0F\x29\x6D*\x0F\x29\x75*\x0F\x29\x7D*\x48\x8D\x9D****\x31\xF6\x49\x89\xFC\x64\x48\x8B\x04\x25****\x48\x89\x85****\x31\xC0\xBA****\x48\x89\xDF\xE8****\x4C\x8D\x8D")
  };

  const std::vector<Symbol> vphysics_CPhysicsEnvironment_SimulateSym = {
    //
    Symbol::FromName("_ZN19CPhysicsEnvironment8SimulateEf"),
    // todo
    NULL_SYMBOL,
  };

  //---------------------------------------------------------------------------------
  // Purpose: tier0 Symbols
  //---------------------------------------------------------------------------------
  const std::vector<Symbol> libtier0_ConMsgSym = {
    //
    Symbol::FromName("ConMsg"),
    //
    Symbol::FromName("_Z6ConMsgPKcz")
  };

  const std::vector<Symbol> libtier0_WarningSym = {
    //
    Symbol::FromName("Warning"),
    //
    Symbol::FromName("Warning")
  };

  const std::vector<Symbol> libtier0_MsgSym = {
    //
    Symbol::FromName("Msg"),
    //
    Symbol::FromName("Msg")
  };
}