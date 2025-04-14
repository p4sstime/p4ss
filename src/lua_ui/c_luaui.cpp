//========= Contributed by 4v4 PASS Time developers. ==========================//
//
// Purpose: Manager for the Lua UI. Wraps around VGUI and 
// allows vgui::Panels
// to be created in C++ and managed by custom defined Lua code.
//=============================================================================//

#ifdef LUAUI
#include "cbase.h"
#include "lua_ui/c_luaui.h"
#include "dbg.h"

static CLuaUiSystem s_pLuaUi;



/// @brief Safe to call multiple times
bool CLuaUiSystem::Init()
{
	return true;
}

void CLuaUiSystem::Shutdown()
{
}

void CLuaUiSystem::Test()
{
	Msg("CLuaUiSystem::Test() called\n");
}

void CLuaUiSystem::Update(float frametime)
{
	// Update the Lua UI
}
CLuaUiSystem* LuaUiSystem()
{
	return &s_pLuaUi;
}

#endif // LUAUI