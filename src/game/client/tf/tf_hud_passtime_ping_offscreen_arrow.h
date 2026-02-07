#ifndef TF_HUD_PASSTIME_PING_OFFSCREEN_ARROW_H
#define TF_HUD_PASSTIME_PING_OFFSCREEN_ARROW_H
#ifdef _WIN32
#pragma once
#endif

#include "tf_hud_passtime_ball_offscreen_arrow.h"

class CTFHudPasstimePingOffscreenArrow : public CTFHudPasstimeOffscreenArrow
{
	DECLARE_CLASS_SIMPLE( CTFHudPasstimePingOffscreenArrow, CTFHudPasstimeOffscreenArrow );
public:
	CTFHudPasstimePingOffscreenArrow( vgui::Panel *pParent, int iIndex );
private:
	virtual C_BaseEntity *PreparePaint( vgui::ImagePanel *pImage, C_TFPlayer *pLocalPlayer ) OVERRIDE;
	int m_iIndex;
	CTFHudPasstimePingOffscreenArrow( vgui::Panel *pParent );
};

#endif // TF_HUD_PASSTIME_PING_OFFSCREEN_ARROW_H
