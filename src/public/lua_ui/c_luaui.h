#ifndef CLUAUI_H
#define CLUAUI_H
#ifdef LUAUI
#ifdef CLIENT_DLL

#ifdef _WIN32
#pragma once
#endif

// Our handle into the Lua UI system.
// Valid at all times after Client DLL is loaded
class C_LuaUi
{
private:
	C_LuaUi();
	~C_LuaUi();
	static C_LuaUi* instance;
public:
	// Call this when Client DLL is loaded.
	static void Init();

	static void Shutdown();

	// Valid at all times after Client DLL is loaded
	static C_LuaUi* Get();

	void Test();

};

#endif // CLIENT_DLL
#endif // LUAUI
#endif // !CLUAUI_H