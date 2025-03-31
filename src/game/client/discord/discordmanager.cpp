#define DISCORDPP_IMPLEMENTATION
#include "discordmanager.h"
#include "discord_social/discordpp.h"
#include <convar.h>

// Discord AppID
static ConVar cl_discord_appid( "cl_discord_appid", "1342303659664609383", FCVAR_DEVELOPMENTONLY | FCVAR_CHEAT );

// Replace with your Discord Application ID
uint64_t APPLICATION_ID = cl_discord_appid.GetInt();

DiscordManager::DiscordManager()
{
	auto client = new discordpp::Client();
}
DiscordManager::~DiscordManager()
{
	// Destructor
}
void DiscordManager::Init()
{

}
void DiscordManager::Shutdown()
{
	
}