//========= Contributed by 4v4 PASS Time developers. ==========================//
//
// Purpose: Manager for the Lua UI.
//
//=============================================================================//

#include "cbase.h"
#include "lua_ui/c_luaui.h"
#include "dbg.h"

C_LuaUi* C_LuaUi::instance = nullptr;
C_LuaUi::C_LuaUi() 
{
}

void C_LuaUi::Init()
{
	if (instance == nullptr)
	{
		instance = new C_LuaUi();
	}
}
C_LuaUi* C_LuaUi::Get()
{
	return instance;
};

void C_LuaUi::Test()
{
	Msg("C_LuaUi::Test() called\n");
}