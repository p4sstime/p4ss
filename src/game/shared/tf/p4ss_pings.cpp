#include "cbase.h"
#include "p4ss_pings.h"

#ifdef GAME_DLL
#include "usermessages.h"
#endif

#include "tier0/memdbgon.h"

CPingSystem *g_pPingSystem = NULL;

CPingSystem::CPingSystem() : CAutoGameSystem( "CPingSystem" )
{
	g_pPingSystem = this;
}

bool CPingSystem::Init()
{
	#ifdef GAME_DLL
		usermessages->Register( "P4ssPing", -1 );
	#endif

	return true;
}

void CPingSystem::LevelInitPreEntity()
{

}

void CPingSystem::Update( float frametime )
{

}

CPingSystem* P4SSPings()
{
	return g_pPingSystem; 
}

#ifdef GAME_DLL
void CPingSystem::PlayerAttemptPing( CBasePlayer *pPlayer )
{
	if ( !pPlayer )
		return;

	if ( !pPlayer->IsPlayer() )
		return;

	Vector vecOrigin = pPlayer->EyePosition();
	Vector vecForward;
	pPlayer->EyeVectors( &vecForward );

	trace_t trace_result;
	UTIL_TraceLine( vecOrigin, vecOrigin + vecForward * 1000.0f, MASK_SOLID, pPlayer, COLLISION_GROUP_NONE, &trace_result );

	if ( trace_result.DidHitWorld() )
	{
		// print success
		DevMsg( "Player %s pinged at position: %f, %f, %f\n",
				pPlayer->GetPlayerName(), trace_result.endpos.x,
				trace_result.endpos.y, trace_result.endpos.z );
	}

}
#endif // GAME_DLL
