#ifndef DISCORDMANAGER_H
#define DISCORDMANAGER_H

#ifdef WIN32
#pragma once
#endif

#ifdef DISCORDSOCIAL
#include "discord_social/discordpp.h"

class DiscordManager
{
	private:
	DiscordManager();
	~DiscordManager();
	static DiscordManager* m_pInstance;

	discordpp::Client* m_pClient;

  public:
	static DiscordManager* Get();
	static void Init();
	static void Shutdown();
};
#endif // DISCORDSOCIAL
#endif // DISCORDMANAGER_H