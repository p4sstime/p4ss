#include "cbase.h"
#include "passtime_pingsystem.h"

#ifdef GAME_DLL
#include "../../server/enginecallback.h"
#endif

#ifdef CLIENT_DLL
#include "c_user_message_register.h"
#include "c_tf_passtime_ping.h"
#include "c_tf_player.h"
#endif

#include "tier0/memdbgon.h"

CPingSystem *g_pPingSystem = NULL;
static CPingSystem g_PingSystem;

CPingSystem::CPingSystem() : CAutoGameSystem( "CPingSystem" ), m_flLastPingTimes( DefLessFunc( int ) )
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

CPingSystem* Passtime_PingSystem()
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

	if ( !pPlayer->IsAlive() || pPlayer->IsObserver() )
		return;

	int iPlayerIndex = pPlayer->entindex();
	int iIndex = m_flLastPingTimes.Find( iPlayerIndex );
	if ( iIndex != m_flLastPingTimes.InvalidIndex() )
	{
		float flLastTime = m_flLastPingTimes[iIndex];
		if ( gpGlobals->curtime < flLastTime + 1.0f )
			return;
	}

	m_flLastPingTimes.InsertOrReplace( iPlayerIndex, gpGlobals->curtime );

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
		CRecipientFilter filter;
		filter.AddRecipientsByTeam( pPlayer->GetTeam() );
		filter.MakeReliable();

		UserMessageBegin( filter, "P4ssPing" );
			WRITE_VEC3COORD( trace_result.endpos );
			WRITE_VEC3COORD( trace_result.plane.normal ); // Send normal
			WRITE_FLOAT( gpGlobals->curtime + 5.0f ); // TODO: make expire time configure by client
			WRITE_SHORT( pPlayer->entindex() );
		MessageEnd();
	}
}
#endif // GAME_DLL

#ifdef CLIENT_DLL

void CPingSystem::CreatePing( const Vector &vecOrigin, const Vector &vecNormal, int iOwnerIndex )
{
	DevMsg( "Received ping at position: %f, %f, %f from player index %d\n",
			vecOrigin.x, vecOrigin.y, vecOrigin.z, iOwnerIndex  );

	C_TFPasstimePing::RemovePingForOwner( iOwnerIndex );

	C_TFPasstimePing *pPing = new C_TFPasstimePing();
	pPing->InitializeAsClientEntity( NULL, RENDER_GROUP_TRANSLUCENT_ENTITY );
	pPing->Spawn();
	pPing->CreatePing( vecOrigin, vecNormal, iOwnerIndex );
}

// recieve usermessage
void __MsgFunc_P4ssPing( bf_read &msg )
{	
	if ( !Passtime_PingSystem() )
		return;

	Vector vecOrigin;
	msg.ReadBitVec3Coord( vecOrigin );
	Vector vecNormal;
	msg.ReadBitVec3Coord( vecNormal );
	float flExpireTime = msg.ReadFloat();
	int iOwnerIndex = msg.ReadShort();
	
	Passtime_PingSystem()->CreatePing( vecOrigin, vecNormal, iOwnerIndex );
}

USER_MESSAGE_REGISTER( P4ssPing );
#endif
