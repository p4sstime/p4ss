"Resource/UI/BaseChat.res"
{
	"HudChat"
	{
		"ControlName"		      "EditablePanel"
		"fieldName" 		      "HudChat"
		"visible" 		          "1"
		"enabled" 		          "1"
		"xpos"			          "3"
		"ypos"			          "r215"
		"wide"	 		          "242"
		"tall"	 		          "110"
		"PaintBackgroundType"  	  "0"
	}

	ChatInputLine
	{
		"ControlName"		      "EditablePanel"
		"fieldName" 		      "ChatInputLine"
		"visible" 		          "1"
		"enabled" 		          "1"
		"xpos"			          "1"
		"ypos"			          "r187"
		"wide"	 		          "237"
		"tall"	 		          "100"
		"PaintBackgroundType"	  "0"
	}

	"ChatFiltersButton"
	{
		"ControlName"		      "Button"
		"fieldName"		          "ChatFiltersButton"
		"xpos"			          "207"
		"ypos"			          "100"
		"wide"			          "36"
		"tall"			          "12"
		"autoResize"		      "1"
		"pinCorner"		          "0"
		"visible"		          "0"
		"enabled"		          "0"
		"tabPosition"		      "0"
		"labelText"		          "chat filter"
		"textAlignment"		      "center"
		"dulltext"		          "0"
		"brighttext"		      "0"
		"Default"		          "0"		
	}

	"HudChatHistory"
	{
		"ControlName"		      "RichText"
		"fieldName"		          "HudChatHistory"
		"xpos"			          "0"
		"ypos"			          "0"
		"wide"	 		          "242"
		"tall"			          "75"
		"wrap"			          "1"
		"autoResize"		      "1"
		"pinCorner"		          "1"
		"visible"		          "1"
		"enabled"		          "1"
		"labelText"		          ""
		"textAlignment"		      "south-west"
		"font"			          "HudFontSmallBold"
		"maxchars"		          "-1"
		"PaintBackgroundType"	  "0"
	}
}
