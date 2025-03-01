"GameMenu" [$WIN32]
{
	"VRModeButton"
	{
		"label" "#MMenu_VRMode_Activate"
		"command" "engine vr_toggle"
		"subimage" "glyph_vr"
		"OnlyWhenVREnabled" "1"
	}

	// These buttons are only shown while in-game
	// and also are positioned by the .res file
	"CallVoteButton"
	{
		"label"			""
		"command"		"callvote"
		"OnlyInGame"	"1"
		"subimage" "icon_checkbox"
		"tooltip" "#MMenu_CallVote"
	}
	"MutePlayersButton"
	{
		"label"			""
		"command"		"OpenMutePlayerDialog"
		"OnlyInGame"	"1"
		"subimage" "glyph_muted"
		"tooltip" "#MMenu_MutePlayers"
	}
	"RequestCoachButton"
	{
		"label"			""
		"command"		"engine cl_coach_find_coach"
		"OnlyInGame"	"1"
		"subimage" "icon_whistle"
		"tooltip" "#MMenu_RequestCoach"
	}
	"ReportPlayerButton"
	{
		"label"			""
		"command"		"OpenReportPlayerDialog"
		"OnlyInGame"	"1"
		"subimage"		"glyph_alert"
		"tooltip"		"#MMenu_ReportPlayer"
	}
	
	"ServerBrowserButton"
	{
		"label" 		"PLAY" 
		"command" 		"OpenServerBrowser"
		"subimage" 		""
	}
	
	"LoadoutButton"
	{
		"label" 		"LOADOUT" 
		"command" 		"engine open_charinfo_direct"
		"subimage" 		""
	}
	
	"LearnButton"
	{
		"label" 		"LEARN" 
		"command" 		"#TF_Training_SelectMode"
		"subimage" 		""
	}
	
		"SettingsButton"
	{
		"label" 		"OPTIONS"
		"command" 		"OpenOptionsDialog"
		"subimage" 		""
	}
	
	"SettingsAdvancedButton"
	{
		"label" 		"ADVANCED OPTIONS"
		"command" 		"opentf2options"
		"subimage" 		""
	}
	
	
			//only shows ingame
	"DisconnectButton"
	{
		"label" 		"DISCONNECT"
		"command" 		"engine disconnect"
		"OnlyInGame"	"1"
		"subimage" 		""
	}
	
		"QuitButton"
	{
		"label" 		"QUIT"
		"command" 		"engine replay_confirmquit"
		"OnlyAtMenu" 	"1"
		"subimage" 		""
	}
}