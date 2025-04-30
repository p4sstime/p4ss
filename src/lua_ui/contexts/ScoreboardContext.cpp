#include "cbase.h"

#ifdef LUAUI
#include "lua.hpp"
#include "sol.hpp"

#include "lua_ui/contexts/Context.h"
#include "lua_ui/contexts/ScoreboardContext.h"


namespace lui
{
ScoreboardContext::ScoreboardContext(::vgui::Panel* parent)
	: Context(parent)
{
	
}
void ScoreboardContext::ShowPanel(bool bShow)
{
	ProtectedCall( "Special_ShowPanel", true, bShow );
}
}
#endif // LUAUI