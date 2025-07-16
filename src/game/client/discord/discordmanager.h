#ifndef DISCORDMANAGER_H
#define DISCORDMANAGER_H

#ifdef WIN32
#pragma once
#endif

#ifdef DISCORDSOCIAL
#include "discord_social/discordpp.h"
#include "igamesystem.h"


class CDiscordManager : public CBaseGameSystemPerFrame
{
	public:
	CDiscordManager() {};

	private:
	discordpp::Client* m_pClient;
	bool m_bReady;
	bool m_bWasShutdown;

  public:
	// methods of IGameSystem
	virtual const char *Name() { return "CDiscordManager"; }
	virtual bool Init();
	virtual void PostInit() {};

	virtual void LevelInitPreEntity();
	virtual void LevelShutdownPreEntity() {};
	virtual void Shutdown();
	virtual void Update( float frametime );
};

extern CDiscordManager *DiscordManager();

#endif // DISCORDSOCIAL
#endif // DISCORDMANAGER_H