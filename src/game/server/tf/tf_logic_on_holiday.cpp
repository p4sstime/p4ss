//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "tf_gamerules.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

class CLogicOnHoliday : public CLogicalEntity
{
	DECLARE_CLASS( CLogicOnHoliday, CLogicalEntity );
	DECLARE_DATADESC();

	COutputEvent m_IsNothing;

	void InputFire( inputdata_t & )
	{
		m_IsNothing.FireOutput( this, this );
	}
};

LINK_ENTITY_TO_CLASS( tf_logic_on_holiday, CLogicOnHoliday );

BEGIN_DATADESC( CLogicOnHoliday )
	DEFINE_INPUTFUNC( FIELD_VOID, "Fire", InputFire ),
	DEFINE_OUTPUT( m_IsNothing, "IsNothing" ),
END_DATADESC()
