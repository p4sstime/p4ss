#ifdef LUAUI
#include "cbase.h"
#include "lua_ui/luipanel.h"
#include "lua_ui/c_luaui.h"
#include "lua_loader.h"
#include "filesystem.h"

namespace lui
{
	Panel::Panel() : Panel::Panel("unnamed") {};
	Panel::Panel(const char* name)
	: m_pName (name)
	, m_L (luaL_newstate())
	{
		luaL_openlibs(m_L);

		if (luaL_dostring(m_L, loader_text) != LUA_OK)
		{
			Error("Error loading Lua UI panel '%s': %s\n", m_pName, lua_tostring(m_L, -1));
			lua_pop(m_L, 1);
			return;
		}
		LuaUiSystem()->RegisterNewItem(this);
	}
	
	Panel::~Panel()
	{
		LuaUiSystem()->DeregisterItem(this);
		lua_close(m_L);
	}

	bool Panel::LoadWithFile(const char* filename)
	{
		if (!g_pFullFileSystem->FileExists(filename))
		{
			Error("Lua UI panel resource file '%s' not found: %s\n", filename, m_pName);
			return false;
		};
		auto file = filesystem->Open(filename, "rb", NULL);
		if (!file)
		{
			Error("Error opening Lua UI panel '%s': %s\n", m_pName, filename);
			return false;
		}
	// load file into a null-terminated buffer
	int fileSize = filesystem->Size( file );
	unsigned bufSize = ((IFileSystem *)filesystem)->GetOptimalReadSize( file, fileSize + 2 );

	char *buffer = (char*)((IFileSystem *)filesystem)->AllocOptimalReadBuffer( file, bufSize );
	Assert( buffer );
	
	// read into local buffer
	bool bRetOK = ( ((IFileSystem *)filesystem)->ReadEx( buffer, bufSize, fileSize, file ) != 0 );

	filesystem->Close( file );	// close file after reading

	// FIXME: it is not guaranteed that filesystem is freed on all paths due to early returns
	if ( bRetOK )
	{
		buffer[fileSize] = 0; // null terminate file as EOF
		buffer[fileSize+1] = 0; // double NULL terminating in case this is a unicode file
		lua_getglobal(m_L, "LOAD");
		lua_pushlstring(m_L, buffer, fileSize);
		lua_pushlstring(m_L, filename, strlen(filename));
		// call LOAD with the user provided buffer
		if ( lua_pcall(m_L, 2, 1, 0) != LUA_OK ) {
			Error("Error running loader for Lua UI panel '%s': %s\n", m_pName, lua_tostring(m_L, -1));
			lua_pop(m_L, 1);

			( (IFileSystem *)filesystem )->FreeOptimalReadBuffer( buffer );
			return false;
		}
		if ( !lua_istable(m_L, -1) )
		{
			Error("Error running loader for Lua UI panel '%s': LOAD(code) failed.", m_pName);
			lua_pop(m_L, 1);

			( (IFileSystem *)filesystem )->FreeOptimalReadBuffer( buffer );
			return false;
		}
		// success, get the returned table for the panel's Lua code
		m_iTableRef = luaL_ref(m_L, LUA_REGISTRYINDEX);
	}
	else
	{
		Error("Error reading file for Lua UI panel '%s': %s\n", m_pName, filename);

		( (IFileSystem *)filesystem )->FreeOptimalReadBuffer( buffer );
		return false;
	}
	( (IFileSystem *)filesystem )->FreeOptimalReadBuffer( buffer );

	// Call env["Init"]()
	lua_rawgeti(m_L, LUA_REGISTRYINDEX, m_iTableRef);
	lua_getfield(m_L, -1, "Init");
	if (!lua_isfunction(m_L, -1))
	{
		Warning("Lua panel %s: Init() was not defined\n", m_pName);
		lua_pop(m_L, 1);
	} else {
		if (lua_pcall(m_L, 0, 0, 0) != LUA_OK)
		{
			Warning("Lua panel '%s': Error running Init: %s\n", m_pName, lua_tostring(m_L, -1));
			lua_pop(m_L, 1);
		}
	}
	lua_pop(m_L, 1); // pop env off stack

	return true;
	}

	void Panel::Update(float frametime)
	{
		lua_getglobal(m_L, "Update");
		if (lua_isfunction(m_L, -1))
		{
			lua_pushnumber(m_L, frametime);
			if (lua_pcall(m_L, 1, 0, 0) != 0)
			{
				DevWarning("Error calling Update: %s\n", lua_tostring(m_L, -1));
				lua_pop(m_L, 1);
			}
		}
	}
}

#endif // LUAUI