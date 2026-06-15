"GameMenu"
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
	
	
			//hahahahahaha all of these labels have to start with a space to make space for the icons 
	
	"ServerBrowserButton"
	{
		"label" 		"#P4SS_Play" 
		"command" 		"OpenServerBrowser"
		"subimage" 		""
	}
	
	"ReplayButtonNoTooltip"
	{
		"label"			"#P4SS_Replay"
		"command"		"engine replay_reloadbrowser"
		"subimage"		""
	}

	"ReplayButton"
	{
		"label"			"                           "
		"command"		""
		"subimage"		""
	}
	
	"EquipButton"
	{
		"label" 		"#P4SS_Equip" 
		"command" 		"engine open_charinfo_direct"
		"subimage" 		""
	}
	
	"LearnButton"
	{
		"label" 		"#P4SS_Learn" 
		"command" 		"#TF_Training_SelectMode"
		"subimage" 		""
	}
	
	"SettingsButton"
	{
		"label" 		"A"
		"command" 		"OpenOptionsDialog"
		"subimage" 		""
		"tooltip"		"#P4SS_Settings"
	}
	
	"SettingsAdvancedButton"
	{
		"label" 		"B"
		"command" 		"opentf2options"
		"tooltip"		"#P4SS_AdvSettings"
	}
	
	"ReportBugButton"
	{
		"label"			"C"
		"command"		"url https://github.com/p4sstime/p4ss/issues"
		"tooltip"		"#P4SS_BugReport"

	}
	"WebsiteButton"
	{
		"label" 		"D"
		"command" 		"url https://passtime.tf"
		"tooltip"		"passtime.tf"
	}
	
	//only shows in-game
	"DisconnectButton"
	{
		"label" 		"#P4SS_Disconnect"
		"command" 		"engine disconnect"
		"OnlyInGame"	"1"
		"subimage" 		""
	}
	
	//only shows on main menu
	"QuitButton"
	{
		"label" 		"#P4SS_Quit"
		"command" 		"engine replay_confirmquit"
		"OnlyAtMenu" 	"1"
		"subimage" 		""
	}
}