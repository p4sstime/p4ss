//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Pass Time goalie heal zone trigger
//
//=============================================================================//

#include "cbase.h"
#include "trigger_passtime_goalie_zone.h"
#include "func_passtime_goalie_zone.h"
#include "tf_player.h"
#include "tf_gamerules.h"
#include "passtime_convars.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//-----------------------------------------------------------------------------
// Redirect old entity name to new implementation for backwards compatibility
LINK_ENTITY_TO_CLASS( trigger_passtime_goalie_zone, CFuncPasstimeGoalieZone );

//-----------------------------------------------------------------------------
BEGIN_DATADESC( CTriggerPasstimeGoalieHeal )
	DEFINE_KEYFIELD( m_flHealAmount, FIELD_FLOAT, "heal_amount" ),
	DEFINE_KEYFIELD( m_flRampUpTime, FIELD_FLOAT, "rampup_time" ),
	DEFINE_KEYFIELD( m_flRampUpMaxMultiplier, FIELD_FLOAT, "rampup_max_mult" ),
	DEFINE_KEYFIELD( m_flHealInterval, FIELD_FLOAT, "heal_interval" ),
	DEFINE_THINKFUNC( HealThink ),
END_DATADESC()

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CTriggerPasstimeGoalieHeal::CTriggerPasstimeGoalieHeal()
{
	m_flHealAmount = 25.0f;
	m_flRampUpTime = 3.0f;
	m_flRampUpMaxMultiplier = 2.0f;
	m_flHealInterval = 0.5f;
}

//-----------------------------------------------------------------------------
// Purpose: Spawn
//-----------------------------------------------------------------------------
void CTriggerPasstimeGoalieHeal::Spawn()
{
	AddSpawnFlags( SF_TRIGGER_ALLOW_CLIENTS );
	BaseClass::Spawn();
	InitTrigger();
	
	SetDefLessFunc( m_mapPlayersInZone );
	
	SetThink( &CTriggerPasstimeGoalieHeal::HealThink );
	SetNextThink( gpGlobals->curtime + m_flHealInterval );
}

//-----------------------------------------------------------------------------
// Purpose: Called when an entity starts touching
//-----------------------------------------------------------------------------
void CTriggerPasstimeGoalieHeal::StartTouch( CBaseEntity *pOther )
{
	BaseClass::StartTouch( pOther );
	
	if ( !pOther || !pOther->IsPlayer() )
		return;
	
	CTFPlayer *pPlayer = ToTFPlayer( pOther );
	if ( !pPlayer || !pPlayer->IsAlive() )
		return;
	
	// Add player to our map if not already there
	EHANDLE hPlayer = pPlayer;
	if ( m_mapPlayersInZone.Find( hPlayer ) == m_mapPlayersInZone.InvalidIndex() )
	{
		PlayerHealInfo_t info;
		info.flEntryTime = gpGlobals->curtime;
		info.flLastHealTime = gpGlobals->curtime;
		info.flAccumulatedHeal = 0.0f;
		m_mapPlayersInZone.Insert( hPlayer, info );
	}
}

//-----------------------------------------------------------------------------
// Purpose: Called when an entity stops touching
//-----------------------------------------------------------------------------
void CTriggerPasstimeGoalieHeal::EndTouch( CBaseEntity *pOther )
{
	BaseClass::EndTouch( pOther );
	
	if ( !pOther || !pOther->IsPlayer() )
		return;
	
	// Remove player from our map
	EHANDLE hPlayer = pOther;
	m_mapPlayersInZone.Remove( hPlayer );
}

//-----------------------------------------------------------------------------
// Purpose: Calculate heal multiplier based on time in zone (ramp-up)
//-----------------------------------------------------------------------------
static float CalculateRampUpMultiplier( float flTimeInZone, float flRampUpTime, float flMaxMultiplier )
{
	if ( flRampUpTime <= 0.0f )
		return flMaxMultiplier;
	
	float flProgress = clamp( flTimeInZone / flRampUpTime, 0.0f, 1.0f );
	return RemapValClamped( flProgress, 0.0f, 1.0f, 1.0f, flMaxMultiplier );
}


//-----------------------------------------------------------------------------
// Purpose: Heal all players in the zone
//-----------------------------------------------------------------------------
void CTriggerPasstimeGoalieHeal::HealThink()
{
	SetNextThink( gpGlobals->curtime + m_flHealInterval );
	
	// Clean up invalid entries and heal valid players
	FOR_EACH_MAP_FAST( m_mapPlayersInZone, i )
	{
		EHANDLE hPlayer = m_mapPlayersInZone.Key( i );
		PlayerHealInfo_t &info = m_mapPlayersInZone[i];
		
		CTFPlayer *pPlayer = ToTFPlayer( hPlayer.Get() );
		
		// Remove invalid or dead players
		if ( !pPlayer || !pPlayer->IsAlive() || !IsTouching( pPlayer ) )
		{
			m_mapPlayersInZone.RemoveAt( i );
			continue;
		}
		
		// Skip if player is at max health
		if ( pPlayer->GetHealth() >= pPlayer->GetMaxHealth() )
			continue;
		
		float flCurrentTime = gpGlobals->curtime;
		float flTimeSinceLastHeal = flCurrentTime - info.flLastHealTime;
		
		// Calculate base heal amount for this interval
		float flHealThisInterval = m_flHealAmount * flTimeSinceLastHeal;
		
		// Apply global scale
		flHealThisInterval *= flGlobalScale;
		
		// Apply ramp-up multiplier
		float flTimeInZone = flCurrentTime - info.flEntryTime;
		float flRampUpMult = CalculateRampUpMultiplier( flTimeInZone, m_flRampUpTime, m_flRampUpMaxMultiplier );
		flHealThisInterval *= flRampUpMult;
		
		// Add to accumulated heal
		info.flAccumulatedHeal += flHealThisInterval;
		info.flLastHealTime = flCurrentTime;
		
		// Apply healing if we have at least 1 HP to give
		int nHealthToAdd = (int)info.flAccumulatedHeal;
		if ( nHealthToAdd > 0 )
		{
			info.flAccumulatedHeal -= nHealthToAdd;
			
			int nActualHeal = pPlayer->TakeHealth( nHealthToAdd, DMG_GENERIC );
			
			if ( nActualHeal > 0 )
			{
				// Fire the player_healonhit event for visual feedback
				IGameEvent *pEvent = gameeventmanager->CreateEvent( "player_healonhit" );
				if ( pEvent )
				{
					pEvent->SetInt( "amount", nActualHeal );
					pEvent->SetInt( "entindex", pPlayer->entindex() );
					gameeventmanager->FireEvent( pEvent );
				}
			}
		}
	}
}
