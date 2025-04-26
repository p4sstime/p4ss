#ifndef LUIPANEL_H
#define LUIPANEL_H
#ifdef LUAUI

#include "cbase.h"
#include "sol.hpp"
#include "vgui_controls/Panel.h"

namespace lui
{
class Context
{
private:
protected:
	sol::table m_luaTable;
	vgui::Panel* m_pPanel;
	CUtlLinkedList<const char*> m_apFileNames;
	sol::state m_L;
	const char* m_pName;

	void Initialize();
	void Clear();
public:
	Context();
	Context(vgui::Panel* parent);
	Context(::lui::Context* parent);
	virtual ~Context();

	bool LoadWithFile(const char* filename, bool addToList = true);
	void SetName(const char* name);
	void Reload();
	virtual const char* Name() const;
	virtual void Update(float frametime);
};
}
#endif // LUAUI
#endif // !LUIPANEL_H