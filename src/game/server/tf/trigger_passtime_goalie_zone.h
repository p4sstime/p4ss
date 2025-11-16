//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Pass Time goalie heal zone trigger
//
//=============================================================================//

#ifndef trigger_passtime_goalie_zone_H
#define trigger_passtime_goalie_zone_H
#ifdef _WIN32
#pragma once
#endif

#include "triggers.h"
#include "utlmap.h"

class CTFPlayer;

//-----------------------------------------------------------------------------
// Purpose: Trigger that heals players inside, with ramp-up and crit heal support
//-----------------------------------------------------------------------------
class CTriggerPasstimeGoalieHeal : public CBaseTrigger
{
public:
	DECLARE_CLASS( CTriggerPasstimeGoalieHeal, CBaseTrigger );
	DECLARE_DATADESC();

	CTriggerPasstimeGoalieHeal();

	virtual void Spawn() OVERRIDE;
	virtual void StartTouch( CBaseEntity *pOther ) OVERRIDE;
	virtual void EndTouch( CBaseEntity *pOther ) OVERRIDE;

	void HealThink();

private:
	struct PlayerHealInfo_t
	{
		float flEntryTime;		// When the player entered the zone
		float flLastHealTime;	// Last time we healed this player
		float flAccumulatedHeal; // Fractional healing accumulator
	};

	CUtlMap<EHANDLE, PlayerHealInfo_t> m_mapPlayersInZone;

	// Keyvalues
	float m_flHealAmount;				// Base heal per second
	float m_flRampUpTime;				// Time to reach max heal rate
	float m_flRampUpMaxMultiplier;		// Max multiplier at full ramp
	
	// Think interval
	float m_flHealInterval;
};

#endif // trigger_passtime_goalie_zone_H
