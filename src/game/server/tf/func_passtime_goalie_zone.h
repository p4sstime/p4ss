//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef FUNC_PASSTIME_GOALIE_ZONE_H
#define FUNC_PASSTIME_GOALIE_ZONE_H
#ifdef _WIN32
#pragma once
#endif

#include "triggers.h"

DECLARE_AUTO_LIST( IFuncPasstimeGoalieZoneAutoList );
class CTFPlayer;

class CFuncPasstimeGoalieZone : public CBaseTrigger, public IFuncPasstimeGoalieZoneAutoList
{
public:
	DECLARE_CLASS( CFuncPasstimeGoalieZone, CBaseTrigger );
	DECLARE_DATADESC();
	
	CFuncPasstimeGoalieZone();
	
	virtual void Spawn() OVERRIDE;
	virtual void StartTouch( CBaseEntity *pOther ) OVERRIDE;
	virtual void EndTouch( CBaseEntity *pOther ) OVERRIDE;

	static bool BPlayerInAny( CTFPlayer *pPlayer );
	static bool BPlayerInFriendly( CTFPlayer *pPlayer );
	static bool BPlayerInEnemy( CTFPlayer *pPlayer );
	static float GetPlayerHealRate( CTFPlayer *pPlayer );
	float GetZoneHealRate( float flTimeSinceDamage ) const;
	
private:
	struct PlayerZoneInfo_t
	{
		float flEntryTime;      // When player entered the zone
		float flLastDamageTime; // Last time player took damage (for heal rate ramp-up)
	};

	CUtlMap<EHANDLE, PlayerZoneInfo_t> m_mapPlayersInZone;

	// Keyvalues
	float m_flMinHealRate;    // Minimum heal rate (HP/s) at start of ramp-up
	float m_flMaxHealRate;    // Maximum heal rate (HP/s) at full ramp-up
	float m_flRampUpDelay;    // Delay before ramp-up starts (seconds)
	float m_flRampUpDuration; // Time to ramp from min to max (seconds)
};

#endif // FUNC_PASSTIME_GOALIE_ZONE_H  
