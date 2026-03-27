//========= Contributed by 4v4 PASS Time developers. ==========================//
//
// Purpose: Utility functions for interacting with TF2 Hud Elements.
//
// $NoKeywords: $
//=============================================================================//

#ifndef PF_UTILS_H
#define PF_UTILS_H
#ifdef _WIN32
#pragma once
#endif

#include "c_tf_player.h"
#include "tf_controls.h"
#include "GameEventListener.h"


#define PF_BLUE Color(137, 184, 214, 255)
#define PF_RED Color(240, 89, 89, 255);
namespace PF 
{
	void ColorTextPF(vgui::TextImage * label, const wchar_t * text, const int team = TF_TEAM_RED);

}

#endif // PF_UTILS_H  