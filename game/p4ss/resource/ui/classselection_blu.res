"Resource/UI/ClassSelection.res"
{
	"class_blue"
	{
    "keyboardinputenabled"    "1"	
	
		
		"TopBorder"
		{
			"ControlName"		"ImagePanel"
			"fieldName"		"TopBorder"
			"xpos"			"c-512"
			"ypos"			"0"
			"zpos"			"3"
			"wide"			"1024"
			"tall"			"64"
			"visible"		"1"
			"enabled"		"1"
			"image"			"../hud/classselect/TopBorder_BLU"
			"scaleImage"		"1"	  
		}
		
		"BottomBorder"
		{
			"ControlName"		"ImagePanel"
			"fieldName"		"BottomBorder"
			"xpos"			"c-512"
			"ypos"			"r64"
			"zpos"			"3"
			"wide"			"1024"
			"tall"			"64"
			"visible"		"1"
			"enabled"		"1"
			"image"			"../hud/classselect/BottomBorder_BLU"
			"scaleImage"		"1"	   
		}
		
		"MainIconLargeWhite"
		{
			"ControlName"		"ImagePanel"
			"fieldName"		"MainIconLargeWhite"
			"xpos"			"c-250"
			"ypos"			"c-250"
			"zpos"			"1"
			"wide"			"500"
			"tall"			"500"
			"visible"		"1"
			"enabled"		"1"
			"image"			"../hud/classselect/MainIconLargeWhite"
			"scaleImage"		"1"	
			"drawcolor"        "104 124 155 255"    //BLU
			"alpha"			"10"
		}
		
		"TFPlayerModel"
		{
			"ControlName"	"CTFPlayerModelPanel"
			"fieldName"		"TFPlayerModel"
			
			"xpos"			"c-450"
			"ypos"			"c-480"
			"zpos"			"2"		
			"wide"			"940"
			"tall"			"760"
			
			"autoResize"	"0"
			"pinCorner"		"0"
			"visible"		"1"
			"enabled"		"1"
			
			"render_texture"	"0"
			"fov"			"25"
			"allow_rot"		"0"

			"paintbackground" "1"		
			"paintbackgroundenabled" "1"
			"bgcolor_override" "255 255 255 0"
			
			"model"
			{
				"force_pos"	"1"

				"angles_x" "0"
				"angles_y" "160"
				"angles_z" "0"
				"origin_x" "400" //forward-back, lower is closer
				"origin_y" "-36" //right-left, higher is lefter
				"origin_z" "-49"
				"frame_origin_x"	"0"
				"frame_origin_y"	"0"
				"frame_origin_z"	"0"
				"spotlight" "1"
			
				"modelname"		""
				"vcd"		"class_select.vcd"
			}
			"lights"
			{
				"spotlight"
				{
					"name"                    "spot"
					"color"                 "0.35 0.35 0.85" //slightly blue
					"attenuation"            "0.9"
					"origin"                "0 0 200"
					"direction"                "320 10 0"
					"inner_cone_angle"        "5"
					"outer_cone_angle"        "200"
					"maxDistance"            "0"
					"exponent"                "5"
				}
			}
		}
	}
}
