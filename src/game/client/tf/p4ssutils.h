//========= Contributed by 4v4 PASS Time developers. ==========================//
//
// Purpose: Utility functions for interacting with TF2 Hud Elements.
//
// $NoKeywords: $
//=============================================================================//

#ifndef P4SSUTILS_H
#define P4SSUTILS_H
#ifdef _WIN32
#pragma once
#endif

#include "c_tf_player.h"
#include "tf_controls.h"
#include "GameEventListener.h"


#define P4SS_BLUE Color(137, 184, 214, 255)
#define P4SS_RED Color(240, 89, 89, 255);
namespace P4ss 
{
	struct ColorChange
	{
		Color color;
		uint64_t idx;
	};
	void ColorTextP4ss(vgui::TextImage * label, const wchar_t * text, const int team = TF_TEAM_RED);
	std::wstring GetColorChanges(const wchar_t *text, const int team, CUtlVector<ColorChange>& colorChanges);
	std::wstring GetColorChangesShadow(const wchar_t *text, const int team, CUtlVector<ColorChange>& colorChanges);
	void SetColors(vgui::TextImage *textImage, CUtlVector<ColorChange>& colorChanges, Color defaultColor = Color( 224, 217, 197, 255));
}

#endif // P4SSUTILS_H  