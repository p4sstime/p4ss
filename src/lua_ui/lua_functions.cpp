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
		int args_oneindexed = args + 1;
		for (int i = 1; i < args_oneindexed; i++)
		{
			message.append(lua_tolstring(L, i, NULL));	
			message.push_back(' ');
		}
		// this should never fire because we check for args < 1 above
		// but it causes SIGABRT on linux if this fails
		if (message.empty())
		{
			Msg("\n");
			return 0;
		}
		
		message.pop_back(); // remove last space
		Msg("%s\n", message.c_str());

		// turns out below is unnecessary since lua clears the stack after a func call
		// // remove all the elements we stacked earlier in the loop
		// lua_pop(L, i);
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