#include "cbase.h"
#include "c_tf_passtime_ping.h"
#include "view.h"
#include "c_tf_player.h"

#include "tier0/memdbgon.h"

CUtlVector<C_TFPasstimePing*> C_TFPasstimePing::s_vecPings;

ConVar tf_passtime_icon_duration( "tf_passtime_ping_duration", "6", FCVAR_CLIENTDLL, "Duration of player pings", true, 0.0f, true, 10.0f );

C_TFPasstimePing::C_TFPasstimePing()
{
	m_flCreationTime = 0.0f;
	m_flExpireTime = 0.0f;
	m_vecNormal.Init();
	InitializeSprites();
}

C_TFPasstimePing::~C_TFPasstimePing()
{
	DestroySprites();
	s_vecPings.FindAndRemove( this );
}

void C_TFPasstimePing::Spawn()
{
	SetNextClientThink( CLIENT_THINK_ALWAYS );

	m_flCreationTime = 0;
	m_flExpireTime = 0;
	s_vecPings.AddToTail( this );
}

void C_TFPasstimePing::RemovePingForOwner( int iOwnerIndex )
{
	for ( int i = s_vecPings.Count() - 1; i >= 0; --i )
	{
		C_TFPasstimePing *pPing = s_vecPings[i];
		if ( pPing && ( pPing->m_iOwnerIndex == iOwnerIndex ) )
		{
			pPing->Release();
		}
	}
}

void C_TFPasstimePing::CreatePing( const Vector &vecOrigin, const Vector &vecNormal, int iOwnerIndex )
{
	SetAbsOrigin( vecOrigin );
	m_vecNormal = vecNormal;
	m_iOwnerIndex = iOwnerIndex;

		DevMsg( "Spawning ping at position: %f, %f, %f\n", GetAbsOrigin().x,
			GetAbsOrigin().y, GetAbsOrigin().z );
	
	m_pSprites[0]->m_FXData.SetOrigin( vecOrigin );
	m_pSprites[0]->m_FXData.SetNormal( vecNormal );

	m_flCreationTime = gpGlobals->curtime;
	m_flExpireTime = gpGlobals->curtime + tf_passtime_icon_duration.GetFloat();

	// Determine color based on team
	float r = 1.0f, g = 1.0f, b = 1.0f;
	C_TFPlayer *pOwner = ToTFPlayer( UTIL_PlayerByIndex( iOwnerIndex ) );
	if ( pOwner )
	{
		if ( pOwner->GetTeamNumber() == TF_TEAM_RED )
		{
			r = 1.0f;
			g = 0.39f;
			b = 0.39f;
		}
		else if ( pOwner->GetTeamNumber() == TF_TEAM_BLUE )
		{
			r = 0.65f;
			g = 0.87f;
			b = 1.0f;
		}
	}

	for ( int i = 0; i < m_pSprites.Count(); ++i )
	{
		m_pSprites[i]->m_FXData.SetColor( r, g, b );
	}

	UpdateVisibility();
}

void C_TFPasstimePing::InitializeSprites()
{
	PrecacheScriptSound( "Halloween.Duck" );

	CFXQuad *pQuad = CreateReticleSprite( "reticles/b4o", 64.0f, 0.0f );
	m_pSprites.AddToTail( pQuad );
	pQuad->m_FXData.SetAlpha( 0.0f, 0.0f );

	pQuad = CreateReticleSprite( "reticles/a6o", 48.0f, 0.0f );
	m_pSprites.AddToTail( pQuad );
	pQuad->m_FXData.SetAlpha( 0.0f, 0.0f );
}

void C_TFPasstimePing::ReloadSprites()
{
	DestroySprites();
	InitializeSprites();
}

void C_TFPasstimePing::DestroySprites()
{
	for ( int i = 0; i < m_pSprites.Count(); ++i )
	{
		clienteffects->RemoveEffect( m_pSprites[i] );
	}
	m_pSprites.RemoveAll();
}

CFXQuad *C_TFPasstimePing::CreateReticleSprite( const char *pMaterialName, float flScale, float flSpinSpeed )
{	
	FXQuadData_t q;
	memset( &q, 0, sizeof( q ) );
	q.m_Color.Init( 1, 1, 1 );
	q.m_flDeltaYaw = flSpinSpeed;
	q.m_flDieTime = FLT_MAX;
	q.m_flEndAlpha = 1;
	q.m_flEndScale = flScale;
	q.m_flLifeTime = 0;
	q.m_flScaleBias = 0;
	q.m_flStartAlpha = 1;
	q.m_flStartScale = flScale;
	q.m_flYaw = 180;
	q.SetMaterial( pMaterialName );
	q.m_uiFlags = 0;
	q.m_vecNormal.Init( 1, 0, 0 );
	q.m_vecOrigin.Init( 0, 0, 0 );
	CFXQuad *pQuad = new CFXQuad( q );
	clienteffects->AddEffect( pQuad );
	return pQuad;
}

void C_TFPasstimePing::ClientThink()
{
	if ( gpGlobals->curtime > m_flExpireTime )
	{
		Release();
		return;
	}

	UpdateVisibility();

	// Fade in
	float flAge = gpGlobals->curtime - m_flCreationTime;
	float flAlpha = RemapValClamped( flAge, 0.0f, 0.25f, 0.0f, 1.0f );
	
	for ( int i = 0; i < m_pSprites.Count(); ++i )
	{
		m_pSprites[i]->m_FXData.SetAlpha( flAlpha, flAlpha );
	}

	if ( m_pSprites.Count() >= 1 )
	{
		m_pSprites[0]->m_FXData.SetOrigin( GetAbsOrigin() + ( m_vecNormal * 2.0f ) );
		m_pSprites[0]->m_FXData.SetNormal( m_vecNormal );
	}

	if ( m_pSprites.Count() >= 2 )
	{
		Vector vecTarget = GetAbsOrigin() + ( m_vecNormal * 32.0f );

		Vector vecToCamera = MainViewOrigin() - vecTarget;
		float flDist = vecToCamera.NormalizeInPlace();

		float flBob = sin( gpGlobals->curtime * 5.0f ) * 2.0f;
		Vector vecBobOffset = m_vecNormal * flBob;

		m_pSprites[1]->m_FXData.SetOrigin( vecTarget + (vecToCamera * 24.0f) + vecBobOffset );

		m_pSprites[1]->m_FXData.SetNormal( vecToCamera ); 

		float flScale = RemapValClamped( flDist, 512.0f, 4096.0f, 64.0f, 256.0f );
		m_pSprites[1]->m_FXData.SetScale( flScale, flScale );
		
		m_pSprites[1]->m_FXData.m_flYaw = 0.0f;
	}
}

int C_TFPasstimePing::DrawModel( int flags )
{
	return 1;
}