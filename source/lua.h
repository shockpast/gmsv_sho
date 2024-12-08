namespace lua
{
  void PushHook(const char* name);
  void ThrowError(const char* error, ...);
  void StartTable();
  void AddFunction(GarrysMod::Lua::CFunc func, const char *name);
  void FinishTable(const char *name);
}