"Resource\training.res"
{
	"soldier"
	{
		"class"				"3" //works, but uses non-standard numbers
		"map"				"tr_throwing_grounds" //works
		"name"				"#TF_Soldier" //seemingly does nothing
		"description"			"#TR_ClassInfo_Soldier" //seemingly does nothing
		"activeImage"			"class_sel_sm_soldier_blu" //seemingly does nothing
		"inactiveImage"			"class_sel_sm_soldier_inactive" //seemingly does nothing
		"video"				"tr_throwing_grounds" //clearly works, a file was specified for each class
	}

	//assume the same for the rest

	//class numbers are probably just their IDs which are:
	//1 : Scout
	//2 : Sniper
	//3 : Soldier
	//4 : Demoman
	//5 : Medic
	//6 : Heavy
	//7 : Pyro
	//8 : Spy
	//9 : Engineer
	
	"demoman"
	{
		"class"				"4"
		"map"				"tr_target"
		"name"				"#TF_Demoman"
		"description"			"#TR_ClassInfo_Demo"
		"locked"				"#TR_Locked_Demo"
		"activeImage"			"class_sel_sm_demo_blu"
		"inactiveImage"			"class_sel_sm_demo_inactive"
		"video"				""
	}
	"medic" //I killed spy
	{
		"class"				"5"
		"map"				"tr_passfortress_test6"
		"name"				"#TF_Medic"
		"description"			"#TR_ClassInfo_Medic"
		"locked"				"#TR_Locked_Medic"
		"activeImage"			"class_sel_sm_spy_blu"
		"inactiveImage"			"class_sel_sm_spy_inactive"
		"video"				""
	}
	"engineer" //idk what we do with this one
	{
		"class"				"9"
		"map"				"tr_target"
		"name"				"#TF_Engineer"
		"description"			"#TR_ClassInfo_Engineer"
		"locked"				"#TR_Locked_Engineer"
		"activeImage"			"class_sel_sm_engineer_blu"
		"inactiveImage"			"class_sel_sm_engineer_inactive"
		"video"				""
	}
}