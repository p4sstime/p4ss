#ifndef LUIPANEL_H
#define LUIPANEL_H
#ifdef LUAUI

#include "cbase.h"
#include "lua.hpp"

namespace lui
{
class Panel
{
private:
	int m_iTableRef;
protected:
	lua_State* m_L;
	const char* m_pName;
public:
	Panel();
	Panel(const char* name);
	~Panel();

	bool LoadWithFile(const char* filename);
	void Update(float frametime);
};
}
#endif // LUAUI
#endif // !LUIPANEL_H