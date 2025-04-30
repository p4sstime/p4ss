#include "cbase.h"

#ifdef LUAUI
#include "lua.hpp"
#include "sol.hpp"

#include "lua_ui/contexts/Context.h"
#include "vgui_controls/Panel.h"


namespace lui
{
class ScoreboardContext : public Context
{
DECLARE_CLASS( ScoreboardContext, Context );
public:
	ScoreboardContext(::vgui::Panel* parent);
	void ShowPanel(bool bShow);
	
};

}
#endif // LUAUI