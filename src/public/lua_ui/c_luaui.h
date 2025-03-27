#ifndef LUI_H
#define LUI_H
#ifdef LUAUI

#ifdef _WIN32
#pragma once
#endif

// Our handle into the Lua UI system.
// Valid at all times after Client DLL is loaded
class C_LuaUi
{
private:
	C_LuaUi();
	static C_LuaUi* instance;
public:
	// Call this when Client DLL is loaded.
	static void Init();

	// Valid at all times after Client DLL is loaded
	static C_LuaUi* Get();

	void Test();

};

#endif // LUAUI
#endif // !LUI_H