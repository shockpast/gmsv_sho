#include <GarrysMod/Lua/Interface.h>
#include <tier1/convar.h>
#include <mathlib/vector.h>
#include <vphysics_interface.h>

#include "vphysics.h"
#include "symbols.h"
#include "detour.h"
#include "main.h"
#include "lua.h"

IPhysics* _physics = NULL;
bool _shouldSimulate = true;

LUA_FUNCTION_STATIC(iphysenv_ShouldSimulate)
{
  _shouldSimulate = LUA->GetBool();
  return 0;
}

LUA_FUNCTION_STATIC(iphysenv_Status)
{
  LUA->PushBool(_shouldSimulate);
  return 1;
}

LUA_FUNCTION_STATIC(iphysenv_SetGravity)
{
  IPhysicsEnvironment* iphysenv = _physics->GetActiveEnvironmentByIndex(0);
  if (iphysenv == NULL)
  {
    LUA->ThrowError("IPhysicsEnvironment couldn't be found, how?");
    return 0;
  }

  if (!LUA->IsType(1, GarrysMod::Lua::Type::Vector))
  {
    lua::ThrowError("bad argument #1 to 'SetGravity' (Vector expected, got %s)", LUA->GetTypeName(1));
    return 0;
  }

  const Vector& vec = LUA->GetVector(1);
  iphysenv->SetGravity(vec);

  return 0;
}

LUA_FUNCTION_STATIC(iphysenv_GetGravity)
{
  IPhysicsEnvironment* iphysenv = _physics->GetActiveEnvironmentByIndex(0);
  if (iphysenv == NULL)
  {
    LUA->ThrowError("IPhysicsEnvironment couldn't be found, how?");
    return 0;
  }

  Vector vec = Vector(0, 0, 0);
  iphysenv->GetGravity(&vec);

  LUA->PushVector(vec);

  return 1;
}

static Detouring::Hook detour_CPhysicsEnvironment_Simulate;
void hook_IPhysicsEnvironment_Simulate(IPhysicsEnvironment* _this, float deltaTime)
{
  if (!_shouldSimulate)
    return;

  detour_CPhysicsEnvironment_Simulate.GetTrampoline<symbols::vphysics_CPhysicsEnvironment_Simulate>()(_this, deltaTime);
}

void vphysics::initialize()
{
  SourceSDK::FactoryLoader vphysics_loader("vphysics");
  _physics = vphysics_loader.GetInterface<IPhysics>(VPHYSICS_INTERFACE_VERSION);

  detour::Create(&detour_CPhysicsEnvironment_Simulate, "CPhysicsEnvironment::Simulate", vphysics_loader.GetModule(), symbols::vphysics_CPhysicsEnvironment_SimulateSym, (void*)hook_IPhysicsEnvironment_Simulate, 0);

  lua::StartTable();
    lua::AddFunction(iphysenv_ShouldSimulate, "ShouldSimulate");
    lua::AddFunction(iphysenv_Status, "Status");
    lua::AddFunction(iphysenv_SetGravity, "SetGravity");
    lua::AddFunction(iphysenv_GetGravity, "GetGravity");
  lua::FinishTable("iphysenv");

  Msg("initialized 'iphysenv' module\n");
}