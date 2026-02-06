#include "cbase.h"
#include "p4ss_pings.h"

#ifdef GAME_DLL
#include "../../server/enginecallback.h"
#endif

#ifdef CLIENT_DLL
#include "c_user_message_register.h"
#endif

#include "tier0/memdbgon.h"

CPingSystem *g_pPingSystem = NULL;
static CPingSystem g_PingSystem;

CPingSystem::CPingSystem() : CAutoGameSystem( "CPingSystem" )
{
	g_pPingSystem = this;
}

bool CPingSystem::Init()
{
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
	UTIL_TraceLine( vecOrigin, vecOrigin + vecForward * 10000.0f, MASK_SOLID, pPlayer, COLLISION_GROUP_NONE, &trace_result );

	if ( trace_result.DidHit() )
	{
		DevMsg( "Player %s pinged at position: %f, %f, %f\n",
				pPlayer->GetPlayerName(), trace_result.endpos.x,
				trace_result.endpos.y, trace_result.endpos.z );

		// broadcast ping
		CBroadcastRecipientFilter filter;
		filter.AddRecipientsByTeam( pPlayer->GetTeam() );
		filter.MakeReliable();

		UserMessageBegin( filter, "P4ssPing" );
			WRITE_VEC3COORD( trace_result.endpos );
			WRITE_FLOAT( gpGlobals->curtime + 5.0f ); // TODO: make expire time configure by client
			WRITE_SHORT( pPlayer->entindex() );
		MessageEnd();
	}

}
#endif // GAME_DLL

#ifdef CLIENT_DLL
void CPingSystem::CreatePing( const Vector &vecOrigin, float flExpireTime, int iOwnerIndex )
{
	PingData_t ping{};
	ping.m_vecOrigin = vecOrigin;
	ping.m_flExpireTime = flExpireTime;
	ping.m_iOwnerIndex = iOwnerIndex;


	DevMsg( "Received ping at position: %f, %f, %f from player index %d\n",
			vecOrigin.x, vecOrigin.y, vecOrigin.z, iOwnerIndex  );

	m_Pings.AddToTail( ping );
}

// recieve usermessage

void __MsgFunc_P4ssPing( bf_read &msg )
{	
	if ( !P4SSPings() )
	{
		Msg( "P4ssPing: Ping system not initialized!\n" );
		return;
	}

	Vector vecOrigin;
	msg.ReadBitVec3Coord( vecOrigin );
	float flExpireTime = msg.ReadFloat();
	int iOwnerIndex = msg.ReadShort();

	if ( !vecOrigin.IsValid() || !flExpireTime || !iOwnerIndex)
	{
		return;
	}

	P4SSPings()->CreatePing( vecOrigin, flExpireTime, iOwnerIndex );
}

USER_MESSAGE_REGISTER( P4ssPing );
#endif
