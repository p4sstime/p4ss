#include "cbase.h"

#ifdef LUAUI
#include "lua.hpp"

#include "lua_functions.h"
#include <string>

namespace CLua
{

	int Print(lua_State* L)
	{
		int args = lua_gettop(L);
		if (args < 1)
		{
			Msg("\n");
			return 0;
		}
		std::string message;
		message.reserve(256);
		int i = 0;
		for (; i < args; i++)
		{
			message.append(lua_tolstring(L, i + 1, NULL));	
			message.push_back(' ');
		}
		message.pop_back(); // remove last space
		Msg("%s\n", message.c_str());
		lua_pop(L, i + 1);
		return 0;
	}
	int Warn(lua_State* L)
	{
		int args = lua_gettop(L);
		if (args < 1)
		{
			ConWarning("\n");
			return 0;
		}
		std::string message;
		message.reserve(256);
		int i = 0;
		for (; i < args; i++)
		{
			message.append(lua_tolstring(L, i + 1, NULL));	
			message.push_back(' ');
		}
		message.pop_back(); // remove last space
		ConWarning("%s\n", message.c_str());
		lua_pop(L, i + 1);
		return 0;
	}
}
#endif