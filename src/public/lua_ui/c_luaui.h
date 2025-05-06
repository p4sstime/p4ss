#ifndef CLUAUI_H
#define CLUAUI_H
#ifdef LUAUI
#ifdef CLIENT_DLL

#ifdef _WIN32
#pragma once
#endif

#include "igamesystem.h"
#include "contexts/Context.h"
// Our handle into the Lua UI system.
// Valid at all times after Client DLL is loaded
class CLuaUiSystem : public CAutoGameSystemPerFrame
{
private:
	CUtlLinkedList<lui::Context *> m_Panels;
	bool bIsShuttingDown = false;
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

	void RegisterNewItem( lui::Context* panel );
	void DeregisterItem( lui::Context* panel );
	void ReloadAll();
	lui::Context* GetFirstChildContext( vgui::Panel* parent )
	{
		FOR_EACH_LL(m_Panels, idx)
		{
			lui::Context* panel = m_Panels[idx];
			if (panel->GetParent() == parent)
				return panel;
		}
		return NULL;
	}

	void Test();

	static void RegisterLuaFunctions( sol::state& L );

};

extern CLuaUiSystem* LuaUiSystem();


#endif // CLIENT_DLL
#endif // LUAUI
#endif // !CLUAUI_H