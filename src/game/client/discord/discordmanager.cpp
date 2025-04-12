#ifdef DISCORDSOCIAL
#define DISCORDPP_IMPLEMENTATION
#include "discordmanager.h"
#include "discord_social/discordpp.h"
#include <convar.h>

// Discord AppID
static ConVar cl_discord_appid( "cl_discord_appid", "1342303659664609383", FCVAR_DEVELOPMENTONLY | FCVAR_CHEAT );

DiscordManager* DiscordManager::m_pInstance = nullptr;
// Replace with your Discord Application ID
uint64_t APPLICATION_ID = cl_discord_appid.GetInt();

DiscordManager::DiscordManager()
{
	m_pClient = new discordpp::Client();
}
DiscordManager::~DiscordManager()
{
	delete m_pClient;
}

void DiscordManager::Init()
{
	m_pInstance = new DiscordManager();	
}
void DiscordManager::Shutdown()
{
	delete m_pInstance;
}
#endif // DISCORDSOCIAL