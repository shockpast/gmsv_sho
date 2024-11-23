// https://github.com/RaphaelIT7/gmod-holylib/blob/main/source/detours.cpp

#include "detour.h"
#include <map>
#include <convar.h>
#include <unordered_set>

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

unsigned int g_pCurrentCategory = 0;
SymbolFinder detour::symFinder;

void* detour::GetFunction(void* module, Symbol symbol)
{
	return symFinder.Resolve(module, symbol.name.c_str(), symbol.length);
}

std::unordered_set<std::string> pDisabledDetours;
std::map<unsigned int, std::vector<Detouring::Hook*>> g_pDetours = {};
void detour::Create(Detouring::Hook* hook, const char* name, void* module, Symbol symbol, void* hook_func, unsigned int category)
{
	if (pDisabledDetours.find(name) != pDisabledDetours.end())
	{
		Msg("detour %s was disabled!\n", name);
		return;
	}

	void* func = detour::GetFunction(module, symbol);
	if (!CheckFunction(func, name))
		return;

	hook->Create(func, hook_func);
	hook->Enable();

	g_pDetours[category].push_back(hook);

	if (!DETOUR_ISVALID((*hook)))
		Msg("failed to detour %s!\n", name);
}

void detour::Remove(unsigned int category) // NOTE: Do we need to check if the provided category is valid?
{
	for (Detouring::Hook* hook : g_pDetours[category]) {
		if (hook->IsEnabled())
		{
			hook->Disable();
			hook->Destroy();
		}
	}
	g_pDetours[category].clear();
}

void detour::ReportLeak()
{
	for (auto& [id, hooks] : g_pDetours)
		if (hooks.size() > 0)
			Msg("ID %d failed to shutdown it's detours!\n", id);
}

static void ToggleDetour(const CCommand& args)
{
	if (args.ArgC() < 1 || V_stricmp(args.Arg(1), "") == 0)
	{
		Msg("disabled detours:\n");
		for (auto it = pDisabledDetours.begin(); it != pDisabledDetours.end(); ++it)
			Msg("	- \"%s\"\n", it->c_str());

		return;
	}

	auto it = pDisabledDetours.find(args.Arg(1));
	if (it != pDisabledDetours.end())
	{
		pDisabledDetours.erase(it);
		Msg("enabled detour %s!\n", args.Arg(1));
		return;
	}

	pDisabledDetours.insert(args.Arg(1));
	Msg("disabled detour %s!\n", args.Arg(1));
}
static ConCommand toggledetour("sho_toggledetour", ToggleDetour, "Debug command. Enables/Disables the given detour.", 0);