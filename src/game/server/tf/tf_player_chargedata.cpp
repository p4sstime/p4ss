//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Server-side message handler for charge angle data
//
//=============================================================================

#include "cbase.h"
#include "tf_player.h"
#include "usermessages.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//-----------------------------------------------------------------------------
// Purpose: Handler for ChargeAngleData user message from client
//-----------------------------------------------------------------------------
class CChargeAngleDataHandler : public CUserMessageHandler
{
public:
    CChargeAngleDataHandler() : CUserMessageHandler("ChargeAngleData") {}

    virtual bool Process(bf_read &msg, IRecipientFilter &filter)
    {
        // Get the originating player
        int playerIndex = filter.GetRecipientIndex(0);
        if (playerIndex <= 0 || playerIndex > gpGlobals->maxClients)
            return false;
            
        CTFPlayer *pPlayer = ToTFPlayer(UTIL_PlayerByIndex(playerIndex));
        if (!pPlayer)
            return false;
            
        // Skip processing if player isn't charging
        if (!pPlayer->m_Shared.InCond(TF_COND_SHIELD_CHARGE))
            return false;

        // Extract charge start info
        float flChargeStartTime = msg.ReadFloat();
        int nChargeStartTick = msg.ReadLong();
        
        // Get number of entries
        int numEntries = msg.ReadByte();
        
        for (int i = 0; i < numEntries; i++)
        {
            float flClientTime = msg.ReadFloat();
            int nClientTick = msg.ReadLong();
            
            QAngle angles;
            angles[PITCH] = msg.ReadFloat();
            angles[YAW] = msg.ReadFloat();
            angles[ROLL] = msg.ReadFloat();
            
            // Process the angle data on the player's shared data
            pPlayer->m_Shared.ProcessClientChargeAngles(flClientTime, nClientTick, angles);
        }

        return true;
    }
};

// Register the handler with the user message system
static CChargeAngleDataHandler s_ChargeAngleDataHandler;
