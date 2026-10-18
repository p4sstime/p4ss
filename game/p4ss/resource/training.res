//NOTE FOR THE OTHER PF DEVS

//If you intend on replacing these maps, you can do so by changing the "map" entries in this file.
//However, when completing a map, your progress is saved via tf_hud_training_complete.cpp, which has its own map list that it checks for.
//Hence, you will need to update both lists to include your new map.
//Each map will need to be distinct for each course, for simplicity's sake and also because the code was originally written to be class-specific. We are hacking our way around it.

"Resource\training.res"
{
	"soldier"
	{
		"class"				"3" //works, but uses non-standard numbers
		"map"				"tr_debug_soldier" //works
		"name"				"" //seemingly does nothing
		"description"			"" //seemingly does nothing
		"activeImage"			"" //seemingly does nothing
		"inactiveImage"			"" //seemingly does nothing
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
		"map"				"tr_debug_demoman"
		"name"				""
		"description"			""
		"locked"				""
		"activeImage"			""
		"inactiveImage"			""
		"video"				""
	}
	"medic"
	{
		"class"				"5"
		"map"				"tr_debug_medic"
		"name"				""
		"description"			""
		"locked"				""
		"activeImage"			""
		"inactiveImage"			""
		"video"				""
	}
	"scout" //Throwing Grounds, Demoman
	{
		"class"				"4"
		"map"				"tr_debug_throwing_grounds"
		"name"				""
		"description"			""
		"locked"				""
		"activeImage"			""
		"inactiveImage"			""
		"video"				""
	}
	"pyro" //tr_passfortress, Medic
	{
		"class"				"5"
		"map"				"tr_debug_passfortress"
		"name"				""
		"description"			""
		"locked"				""
		"activeImage"			""
		"inactiveImage"			""
		"video"				""
	}
	"heavyweapons" //Jack Jumping, Soldier
	{
		"class"				"3"
		"map"				"tr_debug_jackjumping"
		"name"				""
		"description"			""
		"locked"				""
		"activeImage"			""
		"inactiveImage"			""
		"video"				""
	}
	"engineer" //Harder Jumping, Soldier
	{
		"class"				"3"
		"map"				"tr_debug_harderjumping"
		"name"				""
		"description"			""
		"locked"				""
		"activeImage"			""
		"inactiveImage"			""
		"video"				""
	}
	"sniper" //Trimping, Demoman
	{
		"class"				"4"
		"map"				"tr_debug_trimping"
		"name"				""
		"description"			""
		"locked"				""
		"activeImage"			""
		"inactiveImage"			""
		"video"				""
	}
	"spy" //Surfing, Soldier
	{
		"class"				"3"
		"map"				"tr_debug_surfing"
		"name"				""
		"description"			""
		"locked"				""
		"activeImage"			""
		"inactiveImage"			""
		"video"				""
	}
}