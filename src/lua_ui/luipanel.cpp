#include "cbase.h"
#include "lua_ui/luipanel.h"
#include "lua_ui/c_luaui.h"
#include "lua_loader.h"
#include "filesystem.h"
#include "vgui_controls/Panel.h"

#ifdef LUAUI

namespace lui
{
Context::Context() {};
Context::Context( vgui::Panel *parent )
	: m_L(), m_apFileNames(), m_pName( "unnamed" ), m_pPanel( parent )
{
	Initialize();
}

void Context::Clear()
{
	// if (m_iTableRef != LUA_NOREF)
	// {
	// 	luaL_unref(m_L, LUA_REGISTRYINDEX, m_iTableRef);
	// 	m_iTableRef = LUA_NOREF;
	// }
	// lua_close(m_L);
	// m_L = luaL_newstate();
	m_L.~state();
	new ( &m_L ) sol::state();
}
void Context::Initialize()
{
	m_L.open_libraries( sol::lib::base, sol::lib::string, sol::lib::math,
						sol::lib::table, sol::lib::io, sol::lib::os );
	LuaUiSystem()->RegisterLuaFunctions( m_L.lua_state() );
	auto result = m_L.safe_script( loader_text );
	if ( result.status() != sol::call_status::ok )
	{
		sol::error err = result;
		Error( "Error loading Lua UI panel '%s': %s\n", m_pName, err.what() );
		return;
	}
	LuaUiSystem()->RegisterNewItem( this );
}
Context::~Context() { LuaUiSystem()->DeregisterItem( this ); }

void Context::Reload()
{
	this->Clear();
	this->Initialize();
	FOR_EACH_LL( m_apFileNames, i )
	{
		const char *filename = m_apFileNames[i];
		if ( filename )
		{
			LoadWithFile( filename );
		}
	}
}

bool Context::LoadWithFile( const char *filename )
{
	// register this file to run again when we reload
	m_apFileNames.AddToTail( filename );

	if ( !g_pFullFileSystem->FileExists( filename ) )
	{
		Error( "Lua UI panel resource file '%s' not found: %s\n", filename,
			   m_pName );
		return false;
	};
	auto file = filesystem->Open( filename, "rb", NULL );
	if ( !file )
	{
		Error( "Error opening Lua UI panel '%s': %s\n", m_pName, filename );
		return false;
	}
	// load file into a null-terminated buffer
	int fileSize = filesystem->Size( file );
	unsigned bufSize =
	( (IFileSystem *)filesystem )->GetOptimalReadSize( file, fileSize + 2 );

	char *buffer = (char *)( (IFileSystem *)filesystem )
				   ->AllocOptimalReadBuffer( file, bufSize );
	Assert( buffer );

	// read into local buffer
	bool bRetOK = ( ( (IFileSystem *)filesystem )
					->ReadEx( buffer, bufSize, fileSize, file ) != 0 );

	filesystem->Close( file ); // close file after reading

	// FIXME: it is not guaranteed that filesystem is freed on all paths due to
	// early returns
	if ( !bRetOK )
	{
		Error( "Error reading file '%s'", filename );
	}
	buffer[fileSize] = 0; // null terminate file as EOF
	buffer[fileSize + 1] = 0; // double NULL terminating in case this is a unicode file
	sol::protected_function load = m_L.globals().get<sol::protected_function>( "LOAD" );

	auto result = load( buffer, filename );
	if ( !result.valid() )
	{
		sol::error err = result;
		Error( "Error running loader for Lua UI panel '%s': %s\n", m_pName, err.what() );
	}

	int retc = result.return_count();

	if ( retc >= 2 && result[0].get_type() == sol::type::nil )
	{
		Error( "Error running loader for Lua UI panel '%s': %s\n", m_pName, result[1].get<char *>() );
	}
	// lua_getglobal(m_L, "LOAD");
	// lua_pushlstring(m_L, buffer, fileSize);
	// lua_pushlstring(m_L, filename, strlen(filename));
	// // call LOAD with the user provided buffer
	// if ( lua_pcall(m_L, 2, 1, 0) != LUA_OK ) {
	// 	Error("Error running loader for Lua UI panel '%s': %s\n", m_pName,
	// lua_tostring(m_L, -1)); 	lua_pop(m_L, 1); 	goto cleanup;
	// }
	// if ( !lua_istable(m_L, -1) )
	// {
	// 	Error("Error running loader for Lua UI panel '%s': LOAD(code) failed.",
	// m_pName); 	lua_pop(m_L, 1);

	// 	goto cleanup;
	// }
	// success, get the returned table for the panel's Lua code
	if ( result[0].get_type() != sol::type::table )
	{
		Error( "Result from LOAD() was not a table. Panel '%s'. Report this!", m_pName );
	}
	m_luaTable = result[0];

	// success, clean up manually
	( (IFileSystem *)filesystem )->FreeOptimalReadBuffer( buffer );

	auto Init = m_luaTable.get<sol::optional<sol::protected_function>>( "Init" );

	if ( !Init )
	{
		Warning( "Lua panel %s: Init() was not defined\n", m_pName );
		return false;
	}

	sol::function initFunc = *Init;
	initFunc();

	return true;
}

const char *Context::Name() const { return m_pName; }

void Context::SetName( const char *name ) { m_pName = name; }

void Context::Update( float frametime )
{
	auto optional_update = m_luaTable.get<sol::optional<sol::protected_function>>( "Update" );
	if ( !optional_update )
	{
		// Warning( "Lua panel %s: Update() was not defined\n", m_pName );
		return;
	}

	sol::protected_function updateFunc = *optional_update;
	auto result = updateFunc( frametime );

	if (!result.valid() )
	{
		sol::error err = result;
		Warning( "Error running Update() for Lua UI panel '%s': %s\n", m_pName, err.what() );
	}
}
} // namespace lui

#endif // LUAUI