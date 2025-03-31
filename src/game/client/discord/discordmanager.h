#ifndef DISCORDMANAGER_H
#define DISCORDMANAGER_H

#ifdef WIN32
#pragma once
#endif

#ifdef DISCORDSOCIAL

class DiscordManager
{
	private:
	DiscordManager();
	~DiscordManager();
	DiscordManager* m_pInstance;

  public:
	DiscordManager* Get();
	void Init();
	void Shutdown();
};
#endif // DISCORDSOCIAL
#endif // DISCORDMANAGER_H