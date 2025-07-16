#ifdef DISCORDSOCIAL
#define DISCORDPP_IMPLEMENTATION
#include "discordmanager.h"
#include "discord_social/discordpp.h"
#include <convar.h>
#include <thread>

// Discord AppID
static ConVar cl_discord_appid( "cl_discord_appid", "1342303659664609383", FCVAR_DEVELOPMENTONLY | FCVAR_CHEAT );

static CDiscordManager s_pDiscordManager;

// Replace with your Discord Application ID
uint64_t APPLICATION_ID = cl_discord_appid.GetInt();

bool CDiscordManager::Init()
{
	m_pClient = new discordpp::Client();
	m_pClient->SetApplicationId(APPLICATION_ID);
	m_pClient->AddLogCallback( [] (std::string msg, auto severity) {
		switch ( severity )
		{
			case discordpp::LoggingSeverity::None:
				Msg( "[Discord NONE] %s\n", msg.c_str() );
				break;
			case discordpp::LoggingSeverity::Info:
				DevMsg( 1, "[Discord INFO] %s\n", msg.c_str() );
				break;
			case discordpp::LoggingSeverity::Warning:
				Msg( "[Discord WARN] %s\n", msg.c_str() );
				break;
			case discordpp::LoggingSeverity::Error:
				Msg( "[Discord  ERR] %s\n", msg.c_str() );
				break;
			default:
				break;
		}
	}, discordpp::LoggingSeverity::Info ); 
	m_pClient->SetStatusChangedCallback( [this] (auto status, auto err, auto errcode) {
		Msg("[Discord] Client status changed: %s\n", discordpp::Client::StatusToString(status).c_str());
		if ( status == discordpp::Client::Status::Ready )
		{
			this->m_bReady = true;
			Msg( "[Discord] Client is ready\n" );
			
		}
		else if (status == discordpp::Client::Status::Disconnected)
		{
			this->m_bReady = false;
			Msg( "[Discord] Client is disconnected\n" );
		}
		if (err != discordpp::Client::Error::None)
		{
			this->m_bReady = false;
			Msg( "[Discord] Client error! : '%s', error detail %d\n", discordpp::Client::ErrorToString(err).c_str(), errcode );
		}
	} );

	// Create a new activity
discordpp::Activity activity;
activity.SetType(discordpp::ActivityTypes::Playing);
activity.SetDetails("Battle Creek");
activity.SetState("In Competitive Match");

// Update the presence
m_pClient->UpdateRichPresence(activity, [](discordpp::ClientResult result) {
  if (result.Successful()) {
    Msg("✅ Rich presence updated!\n");
  }
});

	discordpp::RunCallbacks();
	return true;
}

void CDiscordManager::LevelInitPreEntity() 
{
	Msg("[Discord] LevelInitPreEntity called, updating rich presence if ready. Ready: %s...\n", m_bReady ? "true" : "false"	);
		discordpp::Activity activity;
		activity.SetType( discordpp::ActivityTypes::Playing );
		activity.SetDetails("Battle Creek");
		activity.SetState( "In a level" );
		// Update the presence
		m_pClient->UpdateRichPresence( activity,
									   []( discordpp::ClientResult result )
									   {
										   if ( result.Successful() )
										   {
											   Msg(
											   "✅ Rich presence updated!\n" );
										   }
									   } );
}

void CDiscordManager::Update(float frametime) 
{
	discordpp::RunCallbacks();
}
void CDiscordManager::Shutdown()
{
	if (m_bWasShutdown)
		return;
	m_bWasShutdown = true;
	printf("CDiscordManager::Shutdown\n");
	discordpp::RunCallbacks();
	m_pClient->Disconnect();
	while (m_pClient->GetStatus() != discordpp::Client::Status::Disconnected)
	{
		discordpp::RunCallbacks();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	m_pClient->Drop();
	delete m_pClient;
}
#endif // DISCORDSOCIAL

CDiscordManager *DiscordManager() { return &s_pDiscordManager; }
