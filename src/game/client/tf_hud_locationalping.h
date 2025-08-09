#ifndef TF_HUD_LOCATIONAL_PING_H
#define TF_HUD_LOCATIONAL_PING_H
#ifdef _WIN32
#pragma once
#endif

#include "utlvector.h"
#include "Color.h"
#include "fx_quad.h"

CFXQuad *CreateReticleSprite( const char *pModelName, float scale,
							  float spinSpeed );
class C_PassTimeLocationalPing
{
  public:
	virtual ~C_PassTimeLocationalPing();
	void OnClientThink();
	virtual void ReloadSprites();

  protected:
	C_PassTimeLocationalPing() {}
	virtual bool Update() = 0;

	CUtlVector<CFXQuad *> m_pSprites;

  private:
	void InitializeSprites();
};