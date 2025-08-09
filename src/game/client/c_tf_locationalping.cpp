#include "cbase.h"
#include "tf_gamerules.h"
#include "c_baseentity.h"
#include "usermessages.h"
#include <tf_hud_passtime_reticle.h>
#include <beamdraw.h>

class C_LocationalPing : public C_BaseEntity
{
	DECLARE_CLASS( C_LocationalPing, C_BaseEntity );

  public:
	void CreatePing();
	virtual int DrawModel( int flags );

	Vector normal;
  private:
	virtual void ClientThink( void );
	C_PasstimeBounceReticle *m_pReticle;

	CountdownTimer m_lifetimeTimer;
};

// Message from server to create the entity
USER_MESSAGE( P4SS_SendPing )
{
	Vector vecPos;
	Vector vecNorm;

	msg.ReadBitVec3Coord( vecPos );
	msg.ReadBitVec3Normal( vecNorm );

	C_LocationalPing *pPing = new C_LocationalPing();

	if ( !pPing )
		return;

	pPing->SetAbsOrigin( vecPos );
	pPing->normal = vecNorm;
	pPing->CreatePing();
}

int C_LocationalPing::DrawModel(int flags) {
	BaseClass::DrawModel(flags);

	    static IMaterial *pMaterial = materials->FindMaterial(
	"replay/replay_balloon_arrow_right", TEXTURE_GROUP_VGUI );

	if ( pMaterial == nullptr || pMaterial->IsErrorMaterial() )
		return 0;


	    Vector vOrigin = GetAbsOrigin();
	float flSize = 16.0f; // Size of the sprite

	// Set up render context
	CMatRenderContextPtr pRenderContext( materials );
	modelrender->ForcedMaterialOverride( pMaterial );

	color32 col;
	col.r = 255;
	col.g = 255;
	col.b = 255;


	// Draw sprite
	DrawSprite( vOrigin, flSize, flSize, col );

	// Clear override
	modelrender->ForcedMaterialOverride( nullptr );
}

void C_LocationalPing::CreatePing() {

	if ( InitializeAsClientEntity( NULL, RENDER_GROUP_OTHER ) == false )
	{
		Release();
		return;
	}
	
	m_pReticle = new C_PasstimeBounceReticle();
	m_lifetimeTimer.Start( 10.0f );

	SetNextClientThink( CLIENT_THINK_ALWAYS );
}

void C_LocationalPing::ClientThink(void){
	if ( m_lifetimeTimer.IsElapsed() )
	{
		m_pReticle->Hide();
		Release();
		return;
	}

	m_pReticle->Show(GetAbsOrigin(), normal);
}