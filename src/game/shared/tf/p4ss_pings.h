//========= Contributed by PASS Fortress Developers. ==========================//
//
// Purpose: Pinging system for Pass Time
//
// $NoKeywords: $
//=============================================================================//

#ifndef P4SS_PINGS_H
#define P4SS_PINGS_H
#ifdef _WIN32
#pragma once
#endif

#include "igamesystem.h"
#include "utlvector.h"

struct PingData_t
{
	Vector m_vecOrigin;
	float m_flExpireTime;
	int m_iOwnerIndex;
};

class CPingSystem : public CAutoGameSystem
{

public:
	CPingSystem();

	virtual bool Init();
	virtual void LevelInitPreEntity();
	virtual void Update( float frametime );

	// server methods
	#ifdef GAME_DLL
	void PlayerAttemptPing( CBasePlayer *pPlayer );
	#endif

	// client methods
	#ifdef CLIENT_DLL
	void CreatePing( const Vector &vecOrigin, float flExpireTime, int iOwnerIndex );
	const CUtlVector<PingData_t> &GetPings() const { return m_Pings; }
	#endif

private:
	CUtlVector<PingData_t> m_Pings;
};

// global
CPingSystem *P4SSPings();

#endif