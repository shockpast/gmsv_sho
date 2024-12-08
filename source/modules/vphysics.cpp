#include <GarrysMod/Lua/Interface.h>
#include <tier1/convar.h>
#include <mathlib/vector.h>
#include <vphysics_interface.h>

#include "helpers/memory.h"
#include "vphysics.h"
#include "symbols.h"
#include "detour.h"
#include "main.h"

typedef void (*IPhysicsEnvironment_Simulate_t)(void* _this, float deltaTime);

IPhysics* _physics = NULL;
bool _shouldSimulate = true;

LUA_FUNCTION_STATIC(iphysenv_ShouldSimulate)
{
  _shouldSimulate = LUA->GetBool();
  return 0;
}

LUA_FUNCTION_STATIC(iphysenv_SetGravity)
{
  IPhysicsEnvironment* iphysenv = _physics->GetActiveEnvironmentByIndex(0);
  const Vector& vec = LUA->GetVector(1);

  iphysenv->SetGravity(vec);

  return 0;
}

static Detouring::Hook detour_CPhysicsEnvironment_Simulate;
void hook_IPhysicsEnvironment_Simulate(IPhysicsEnvironment* _this, float deltaTime)
{
  if (!_shouldSimulate)
    return;

  detour_CPhysicsEnvironment_Simulate.GetTrampoline<IPhysicsEnvironment_Simulate_t>()(_this, deltaTime);
}

void vphysics::initialize()
{
  SourceSDK::FactoryLoader vphysics_loader("vphysics");
  _physics = vphysics_loader.GetInterface<IPhysics>(VPHYSICS_INTERFACE_VERSION);

  detour::Create(&detour_CPhysicsEnvironment_Simulate, "CPhysicsEnvironment::Simulate", vphysics_loader.GetModule(), symbols::vphysics_CPhysicsEnvironment_SimulateSym, (void*)hook_IPhysicsEnvironment_Simulate, 0);

  g_Lua->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
  g_Lua->CreateTable();
    g_Lua->PushCFunction(iphysenv_ShouldSimulate);
    g_Lua->SetField(-2, "ShouldSimulate");
    g_Lua->PushCFunction(iphysenv_SetGravity);
    g_Lua->SetField(-2, "SetGravity");
  g_Lua->SetField(-2, "iphysenv");
  g_Lua->Pop();

  Msg("initialized 'iphysenv' module\n");
}