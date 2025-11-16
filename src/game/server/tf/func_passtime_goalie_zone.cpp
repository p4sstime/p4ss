//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "func_passtime_goalie_zone.h"
#include "tf_player.h"
#include "tf_gamerules.h"
#include "passtime_convars.h"

#include "tier0/memdbgon.h"

//-----------------------------------------------------------------------------
BEGIN_DATADESC( CFuncPasstimeGoalieZone )
	DEFINE_KEYFIELD( m_flMinHealRate,    FIELD_FLOAT, "min_heal_rate" ),
	DEFINE_KEYFIELD( m_flMaxHealRate,    FIELD_FLOAT, "max_heal_rate" ),
	DEFINE_KEYFIELD( m_flRampUpDelay,    FIELD_FLOAT, "rampup_delay" ),
	DEFINE_KEYFIELD( m_flRampUpDuration, FIELD_FLOAT, "rampup_duration" ),
END_DATADESC()

//-----------------------------------------------------------------------------
LINK_ENTITY_TO_CLASS( func_passtime_goalie_zone, CFuncPasstimeGoalieZone )

IMPLEMENT_AUTO_LIST( IFuncPasstimeGoalieZoneAutoList );

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CFuncPasstimeGoalieZone::CFuncPasstimeGoalieZone()
{
	m_flMinHealRate    = 0.0f;
	m_flMaxHealRate    = 0.0f;
	m_flRampUpDelay    = 0.0f;
	m_flRampUpDuration = 10.0f; // 10 second ramp-up by default
}

//-----------------------------------------------------------------------------
void CFuncPasstimeGoalieZone::Spawn() 
{
	AddSpawnFlags( SF_TRIGGER_ALLOW_CLIENTS );
	BaseClass::Spawn();
	InitTrigger();
	
	SetDefLessFunc( m_mapPlayersInZone );
}

//-----------------------------------------------------------------------------
bool CFuncPasstimeGoalieZone::BPlayerInAny( CTFPlayer *pPlayer )
{
	auto &all = AutoList();
	for ( int i = 0; i < all.Count(); ++i )
	{
		auto *pZone = (CFuncPasstimeGoalieZone *)all[i];
		if ( pZone->IsTouching( pPlayer ) )
			return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
bool CFuncPasstimeGoalieZone::BPlayerInFriendly( CTFPlayer *pPlayer )
{
	auto &all = AutoList();
	int iPlayerTeam = pPlayer->GetTeamNumber();
	for ( int i = 0; i < all.Count(); ++i )
	{
		auto *pZone = (CFuncPasstimeGoalieZone *)all[i];
		if ( (pZone->GetTeamNumber() == iPlayerTeam) && pZone->IsTouching( pPlayer ) )
			return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
bool CFuncPasstimeGoalieZone::BPlayerInEnemy( CTFPlayer *pPlayer )
{
	auto &all = AutoList();
	int iPlayerTeam = pPlayer->GetTeamNumber();
	for ( int i = 0; i < all.Count(); ++i )
	{
		auto *pZone = (CFuncPasstimeGoalieZone *)all[i];
		if ( (pZone->GetTeamNumber() != iPlayerTeam) && pZone->IsTouching( pPlayer ) )
			return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
// Purpose: Called when an entity starts touching
//-----------------------------------------------------------------------------
void CFuncPasstimeGoalieZone::StartTouch( CBaseEntity *pOther )
{
	BaseClass::StartTouch( pOther );
	
	if ( !pOther || !pOther->IsPlayer() )
		return;
	
	// Add player to our map if not already there
	EHANDLE hPlayer = pOther;
	if ( m_mapPlayersInZone.Find( hPlayer ) == m_mapPlayersInZone.InvalidIndex() )
	{
		PlayerZoneInfo_t info;
		info.flEntryTime = gpGlobals->curtime;
		// Initialize with player's actual last damage time
		CTFPlayer *pPlayer = ToTFPlayer( pOther );
		info.flLastDamageTime = pPlayer ? pPlayer->GetLastDamageReceivedTime() : 0.0f;
		m_mapPlayersInZone.Insert( hPlayer, info );
	}
}

//-----------------------------------------------------------------------------
// Purpose: Called when an entity stops touching
//-----------------------------------------------------------------------------
void CFuncPasstimeGoalieZone::EndTouch( CBaseEntity *pOther )
{
	BaseClass::EndTouch( pOther );
	
	if ( !pOther || !pOther->IsPlayer() )
		return;
	
	// Remove player from our map
	EHANDLE hPlayer = pOther;
	m_mapPlayersInZone.Remove( hPlayer );
}

//-----------------------------------------------------------------------------
// Purpose: Calculate heal rate for a zone based on time since damage
//-----------------------------------------------------------------------------
float CFuncPasstimeGoalieZone::GetZoneHealRate( float flTimeSinceDamage ) const
{
	// Before delay: use min rate
	if ( flTimeSinceDamage < m_flRampUpDelay )
		return m_flMinHealRate;
	
	// After delay: ramp from min to max over duration
	float flTimeSinceDelay = flTimeSinceDamage - m_flRampUpDelay;
	
	// If no duration or already past duration: use max rate
	if ( m_flRampUpDuration <= 0.0f || flTimeSinceDelay >= m_flRampUpDuration )
		return m_flMaxHealRate;
	
	// Linear interpolation from min to max
	float flProgress = flTimeSinceDelay / m_flRampUpDuration;
	return RemapValClamped( flProgress, 0.0f, 1.0f, m_flMinHealRate, m_flMaxHealRate );
}

//-----------------------------------------------------------------------------
// Purpose: Get heal rate for a player in any zone (0.0 if not in zone)
//-----------------------------------------------------------------------------
float CFuncPasstimeGoalieZone::GetPlayerHealRate( CTFPlayer *pPlayer )
{
	auto &all = AutoList();
	for ( int i = 0; i < all.Count(); ++i )
	{
		auto *pZone = (CFuncPasstimeGoalieZone *)all[i];
		if ( pZone->IsTouching( pPlayer ) )
		{
			EHANDLE hPlayer = pPlayer;
			int idx = pZone->m_mapPlayersInZone.Find( hPlayer );
			if ( idx != pZone->m_mapPlayersInZone.InvalidIndex() )
			{
				// Calculate time since player's last damage
				float flTimeSinceDamage = gpGlobals->curtime - pPlayer->GetLastDamageReceivedTime();
				return pZone->GetZoneHealRate( flTimeSinceDamage );
			}
		}
	}
	return 0.0f;
}
