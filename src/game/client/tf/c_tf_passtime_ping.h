#ifndef C_TF_PASSTIME_PING_H
#define C_TF_PASSTIME_PING_H

#include "cbase.h"
#include "fx_quad.h"

class C_TFPasstimePing : public C_BaseEntity
{
	DECLARE_CLASS( C_TFPasstimePing, C_BaseEntity );

public:
	C_TFPasstimePing();
	virtual ~C_TFPasstimePing();

	void CreatePing( const Vector &vecOrigin, const Vector &vecNormal, int iOwnerIndex  );

	virtual void Spawn();
	virtual void ClientThink();
	virtual int DrawModel( int flags );

	virtual RenderGroup_t GetRenderGroup() OVERRIDE { return RENDER_GROUP_TRANSLUCENT_ENTITY; };

	CFXQuad *CreateReticleSprite( const char *pMaterialName, float flScale, float flSpinSpeed );
	CUtlVector<CFXQuad*> m_pSprites;

private:
	void InitializeSprites();
	void ReloadSprites();
	void DestroySprites();

	float m_flCreationTime;
	float m_flExpireTime;
	Vector m_vecNormal;
};



#endif