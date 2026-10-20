"Resource/UI/HudItemEffectMeter.res"
{
	HudItemEffectMeter
	{
		"fieldName"		"HudItemEffectMeter"
		"visible"		"1"
		"enabled"		"1"
		"xpos"			"r162"	[$WIN32]
		"xpos_minmode"	"c-184"	[$WIN32]
		"ypos"			"r52"	[$WIN32]
		"ypos_minmode"	"r158"	[$WIN32]
		"wide"			"100"
		"tall"			"50"
		"MeterFG"		"White"
		"MeterBG"		"Gray"
	}
	
	"GreyBG"
	{
		"ControlName"	"CTFImagePanel"
		"fieldName"		"GreyBG"
		"xpos"			"2"
		"xpos_minmode"	"-6"
		"ypos"			"0"
		"ypos_minmode"	"0"
		"zpos"			"-1"
		"wide"			"74"
		"wide_minmode"	"62"
		"tall"			"24"
		"tall_minmode"	"21"
		"visible"		"1"
		"enabled"		"1"
		"image"			"../hud/ammo_grey_bg"
		"scaleImage"	"1"	
		"pin_to_sibling"	"ItemEffectMeterBG"
		"pin_corner_to_sibling" "PIN_TOP_CENTER"
		"pin_to_sibling_corner" "PIN_TOP_CENTER"
	}

	
	"ItemEffectMeterBG"
	{
		"ControlName"	"CTFImagePanel"
		"fieldName"		"ItemEffectMeterBG"
		"xpos"			"14"
		"xpos_minmode"	"14"
		"ypos"			"15"
		"ypos_minmode"	"15"
		"zpos"			"0"
		"wide"			"70"
		"wide_minmode"	"70"
		"tall"			"26"
		"visible"		"0"
		"visible_minmode"	"0"
		"image"			"../hud/misc_ammo_area_horiz1_blue"
		"scaleImage"	"1"	
		"teambg_2"		"../hud/misc_ammo_area_horiz1_red"
		"teambg_2_lodef"	"../hud/misc_ammo_area_red_lodef"
		"teambg_3"		"../hud/misc_ammo_area_horiz1_blue"
		"teambg_3_lodef"	"../hud/misc_ammo_area_blue_lodef"				
	}
	
	"ItemEffectMeterLabel"
	{
		"ControlName"			"CExLabel"
		"fieldName"				"ItemEffectMeterLabel"
		"xpos"					"25"
		"xpos_minmode"			"30"
		"ypos"					"19"
		"ypos_minmode"			"20"
		"zpos"					"2"
		"wide"					"46"
		"wide_minmode"			"40"
		"tall"					"16"
		"tall_minmode"			"10"
		"autoResize"			"1"
		"pinCorner"				"2"
		"visible"				"1"
		"enabled"				"0"
		"tabPosition"			"0"
		"labelText"				"#TF_Ball"
		"textAlignment"			"center"
		"dulltext"				"0"
		"brighttext"			"0"
		"font"					"MontserratBlack14"
		"font_minmode"			"MontserratBlack12"
		"disabledfgcolor2_override"		"TanDark"
	}

	"ItemEffectMeter"
	{	
		"ControlName"			"ContinuousProgressBar"
		"fieldName"				"ItemEffectMeter"
		"font"					"Default"
		"xpos"					"15"
		"ypos"					"23"
		"ypos_minmode"			"22"
		"xpos_minmode"			"22"
		"zpos"					"2"
		"wide"					"68"
		"wide_minmode"			"57"
		"tall"					"8"	
		"tall_minmode"			"7"				
		"autoResize"			"0"
		"pinCorner"				"0"
		"visible"				"1"
		"enabled"				"1"
		"textAlignment"			"Left"
		"dulltext"				"0"
		"brighttext"			"0"
	}					
}
