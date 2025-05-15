// Created by Crowbar 0.74

$modelname "props_pf/shrub_pfc.mdl"

$staticprop

$bodygroup "Body"
{
	studio "shrub_pfc.dmx"
}


$surfaceprop "foliage"

$contents "solid"

$illumposition 1.736 0.866 20.897

$cdmaterials "models\props_pf\"

$texturegroup "skinfamilies"
{
	{ "shrub_pf_grassland"	}
	{ "shrub_pf_badlands"	}
	{ "shrub_pf_taiga"		}
	{ "shrub_pf_swamp"		}
	{ "shrub_pf_desert"		}
	{ "shrub_pf_tundra"		}
	{ "shrub_pf_pyroland"	}
}

$cbox 0 0 0 0 0 0

$bbox -35.617 -21.888 -2.916 33.885 25.361 44.709

$definebone "static_prop" "" 0 0 0 0 0 0 0 0 0 0 0 0


$sequence "idle" {
	"shrub_pfc.dmx"
	fadein 0.2
	fadeout 0.2
	fps 30
}
