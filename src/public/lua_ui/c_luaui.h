#ifndef CLUAUI_H
#define CLUAUI_H
#ifdef LUAUI
#ifdef CLIENT_DLL

#ifdef _WIN32
#pragma once
#endif

#include "igamesystem.h"
#include "luipanel.h"
// Our handle into the Lua UI system.
// Valid at all times after Client DLL is loaded
class CLuaUiSystem : public CAutoGameSystemPerFrame
{
private:
	CUtlLinkedList<lui::Panel *> m_Panels;
public:
	CLuaUiSystem() 
	: m_Panels () 
	{};
	// Call this when Client DLL is loaded.
	virtual const char *Name() override { return "CLuaUiSystem"; }
	virtual bool Init() override;
	virtual void PostInit() {};
	virtual void Shutdown();
	virtual void Update( float frametime );

	void RegisterNewItem( lui::Panel* panel );
	void DeregisterItem( lui::Panel* panel );

	void Test();

};

extern CLuaUiSystem* LuaUiSystem();


#endif // CLIENT_DLL
#endif // LUAUI
#endif // !CLUAUI_H