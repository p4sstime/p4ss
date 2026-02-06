#include "cbase.h"
#include "c_tf_passtime_ping.h"
#include "view.h"

#include "tier0/memdbgon.h"

ConVar tf_passtime_icon_duration( "tf_passtime_icon_duration", "5", FCVAR_CLIENTDLL, "Duration of the passtime ping icon.", true, 0.0f, true, 10.0f );

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
}

void C_TFPasstimePing::Spawn()
{
	SetNextClientThink( CLIENT_THINK_ALWAYS );

	m_flCreationTime = 0;
	m_flExpireTime = 0;
}

void C_TFPasstimePing::CreatePing( const Vector &vecOrigin, const Vector &vecNormal, int iOwnerIndex )
{
	SetAbsOrigin( vecOrigin );
	m_vecNormal = vecNormal;

		DevMsg( "Spawning ping at position: %f, %f, %f\n", GetAbsOrigin().x,
			GetAbsOrigin().y, GetAbsOrigin().z );
	
	m_pSprites[0]->m_FXData.SetOrigin( vecOrigin );
	m_pSprites[0]->m_FXData.SetNormal( vecNormal );

	m_flCreationTime = gpGlobals->curtime;
	m_flExpireTime = gpGlobals->curtime + tf_passtime_icon_duration.GetFloat();

	UpdateVisibility();
}

void C_TFPasstimePing::InitializeSprites()
{
	CFXQuad *pQuad = CreateReticleSprite( "reticles/b4o", 64.0f, 0.0f );
	m_pSprites.AddToTail( pQuad );
	
	// arrow
	pQuad = CreateReticleSprite( "reticles/a2o", 48.0f, 0.0f );
	m_pSprites.AddToTail( pQuad );
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
		DestroySprites();
		return;
	}

	UpdateVisibility();

	if ( m_pSprites.Count() >= 1 )
	{
		m_pSprites[0]->m_FXData.SetOrigin( GetAbsOrigin() + ( m_vecNormal * 2.0f ) );
		m_pSprites[0]->m_FXData.SetNormal( m_vecNormal );
	}

	if ( m_pSprites.Count() >= 2 )
	{
		float flBobHeight = 20.0f;
		float flBobSpeed = 2.0f;
		float flOffset = 32.0f + ( sin( gpGlobals->curtime * flBobSpeed ) * flBobHeight );
		
		Vector vecOrigin = GetAbsOrigin() + ( m_vecNormal * flOffset );
		m_pSprites[1]->m_FXData.SetOrigin( vecOrigin );

		Vector vecToCamera = MainViewOrigin() - vecOrigin;
		Vector vecProjected = vecToCamera - ( m_vecNormal * vecToCamera.Dot( m_vecNormal ) );
		vecProjected.NormalizeInPlace();
		
		if ( vecProjected.IsZero() )
		{
			Vector vecRight, vecUp;
			VectorVectors( m_vecNormal, vecRight, vecUp );
			vecProjected = vecRight;
		}

		m_pSprites[1]->m_FXData.SetNormal( vecProjected );
	}
}

int C_TFPasstimePing::DrawModel( int flags )
{
	return 1;
}