#ifndef CLUAUI_H
#define CLUAUI_H
#ifdef LUAUI
#ifdef CLIENT_DLL

#ifdef _WIN32
#pragma once
#endif

#include "igamesystem.h"
// Our handle into the Lua UI system.
// Valid at all times after Client DLL is loaded
class CLuaUiSystem : public CAutoGameSystemPerFrame
{
private:
public:
	CLuaUiSystem() {};
	// Call this when Client DLL is loaded.
	virtual const char *Name() override { return "CLuaUiSystem"; }
	virtual bool Init() override;
	virtual void PostInit() {};
	virtual void Shutdown();
	virtual void Update( float frametime );

	// Valid at all times after Client DLL is loaded
	static CLuaUiSystem* Get();

	void Test();

};

extern CLuaUiSystem* LuaUiSystem();


#endif // CLIENT_DLL
#endif // LUAUI
#endif // !CLUAUI_H