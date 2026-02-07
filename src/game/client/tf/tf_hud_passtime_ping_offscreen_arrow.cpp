#include "cbase.h"
#include "tf_hud_passtime_ping_offscreen_arrow.h"
#include "c_tf_passtime_ping.h"
#include "c_tf_player.h"
#include <vgui_controls/ImagePanel.h>

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

CTFHudPasstimePingOffscreenArrow::CTFHudPasstimePingOffscreenArrow( vgui::Panel *pParent, int iIndex )
	: BaseClass( pParent, "PasstimePingOffscreenArrow" )
	, m_iIndex( iIndex )
{
}

C_BaseEntity *CTFHudPasstimePingOffscreenArrow::PreparePaint( vgui::ImagePanel *pImage, C_TFPlayer *pLocalPlayer )
{
	if ( !pImage || !pLocalPlayer )
	{
		return NULL;
	}

	const CUtlVector<C_TFPasstimePing*>& vecPings = C_TFPasstimePing::GetPings();
	if ( m_iIndex >= vecPings.Count() )
	{
		return NULL;
	}

	C_TFPasstimePing *pPing = vecPings[m_iIndex];
	if ( !pPing )
	{
		return NULL;
	}

	SetAlpha( 255 );
    
	if ( pImage )
	{
		pImage->SetImage( "../reticles/a6o" );
	}

	return pPing;
}
