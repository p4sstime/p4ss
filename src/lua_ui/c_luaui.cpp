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
#include "lua.hpp"
#include "lua_loader.h"

static CLuaUiSystem s_pLuaUi;



/// @brief Safe to call multiple times
bool CLuaUiSystem::Init()
{
	return true;
}

void CLuaUiSystem::RegisterNewItem(lui::Panel* panel)
{
	// Register the new item with Lua
	// This is where we store the panel in the list of things to call per frame
	Msg("CLuaUiSystem::RegisterNewItem() called\n");
	
	m_Panels.AddToTail(panel);
}

void CLuaUiSystem::DeregisterItem(lui::Panel* panel)
{
	// De-register the item from Lua
	// This is where we remove the panel from the list of things to call per frame
	Msg("CLuaUiSystem::DeRegisterItem() called\n");
	
	m_Panels.FindAndRemove(panel);
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
	FOR_EACH_LL(m_Panels, i)
	{
		lui::Panel* panel = m_Panels[i];
		panel->Update(frametime);
	}
}
CLuaUiSystem* LuaUiSystem()
{
	return &s_pLuaUi;
}

#endif // LUAUI