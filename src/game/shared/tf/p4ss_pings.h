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

	#endif

};

// global
CPingSystem *P4SSPings();

#endif