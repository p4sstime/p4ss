//========= Contributed by 4v4 PASS Time developers. ==========================//
//
// Purpose: Manager for the Lua UI. Wraps around VGUI and 
// allows vgui::Panels
// to be created in C++ and managed by custom defined Lua code.
//=============================================================================//

#include "cbase.h"

#ifdef LUAUI
 
#include "lua_ui/c_luaui.h"
#include "dbg.h"
#include "lua.hpp"
#include "lua_loader.h"
#include "lua_functions.h"

static CLuaUiSystem s_pLuaUi;

ConCommand lua_reload("lua_reload", [] () {LuaUiSystem()->ReloadAll();}, "Reload all Lua UI panels", FCVAR_CLIENTCMD_CAN_EXECUTE);



/// @brief Safe to call multiple times
bool CLuaUiSystem::Init()
{
	return true;
}

void CLuaUiSystem::RegisterNewItem(lui::Context* panel)
{
	// Register the new item with Lua
	// This is where we store the panel in the list of things to call per frame
	Msg("CLuaUiSystem::RegisterNewItem\n");
	
	m_Panels.AddToTail(panel);
}

void CLuaUiSystem::DeregisterItem(lui::Context* panel)
{
	// De-register the item from Lua
	// This is where we remove the panel from the list of things to call per frame
	Msg("CLuaUiSystem::DeRegisterItem() called\n");
	
	m_Panels.FindAndRemove(panel);
}
void CLuaUiSystem::Shutdown()
{
}

void CLuaUiSystem::RegisterLuaFunctions(lua_State *L)
{
	// Register the Lua functions
	Msg("CLuaUiSystem::RegisterLuaFunctions() called\n");
	lua_register(L, "Print", CLua::Print);
	lua_register(L, "Warn", CLua::Warn);
}

void CLuaUiSystem::Test()
{
	Msg("CLuaUiSystem::Test() called\n");
}

void CLuaUiSystem::Update(float frametime)
{
	// Update the Lua UI
	FOR_EACH_LL(m_Panels, i)
	{
		lui::Context* panel = m_Panels[i];
		panel->Update(frametime);
	}
}

void CLuaUiSystem::ReloadAll()
{
	// Reload all Lua UI panels
	Msg("CLuaUiSystem::ReloadAll() called\n");
	FOR_EACH_LL(m_Panels, i)
	{
		lui::Context* panel = m_Panels[i];
		panel->Reload();
	}
}
CLuaUiSystem* LuaUiSystem()
{
	return &s_pLuaUi;
}

#endif // LUAUI