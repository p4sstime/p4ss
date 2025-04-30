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
	vgui::Panel *m_pParentPanel;
	CUtlLinkedList<const char *> m_apFileNames;
	sol::state m_L;
	const char *m_pName;

	

	template <typename T, typename... Args>
	bool ProtectedCall( T &&funcName, bool shouldLog, Args &&...args )
	{
		auto func =
		m_luaTable.get<sol::optional<sol::protected_function>>( funcName );

		if ( !func )
		{
			Warning( "Lua panel %s: Init() was not defined\n", m_pName );
			return false;
		}

		sol::protected_function initFunc = *func;

		auto result = initFunc( std::forward<Args...>( args )... );
		if ( !result.valid() )
		{
			if ( shouldLog )
			{
				sol::error err = result;
				if constexpr ( std::is_same<T, const char *>::value )
				{
					const char *funcName = funcName;
					Warning( "Error pcalling %s() for Lua UI panel '%s': %s\n",
							 funcName, m_pName, err.what() );
				}
				else
				{
					Warning( "Error pcalling for Lua UI panel '%s': %s\n",
							 m_pName, err.what() );
				}
			}
			return false;
		}

		return true;
	}

  public:
	Context();
	Context( vgui::Panel *parent );
	Context( ::lui::Context *parent );
	virtual ~Context();

	// DO NOT call this if you are not ACUTELY aware of what you are doing.
	// This is used to *reinitialize* the Lua state.
	void Initialize();
	// DO NOT call this if you are not ACUTELY aware of what you are doing.
	// This is used to clear the Lua state.
	void Clear();

	vgui::Panel *GetParent() { return m_pParentPanel; }
	bool LoadWithFile( const char *filename, bool addToList = true );
	void SetName( const char *name );
	void Reload();
	virtual const char *Name() const;
	virtual void Update( float frametime );
};
} // namespace lui
#endif // LUAUI
#endif // !LUIPANEL_H