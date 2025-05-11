//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Client handler for charge angle data message
//
//=============================================================================

#include "cbase.h"
#include "hudelement.h"
#include "c_tf_player.h"
#include "tf_hud_chargedata.h"
#include "usermessages.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//-----------------------------------------------------------------------------
// Purpose: Handler for the ChargeAngleData user message
//-----------------------------------------------------------------------------
void __MsgFunc_ChargeAngleData(bf_read &msg)
{
    // Skip processing if not local player
    C_TFPlayer *pLocalPlayer = C_TFPlayer::GetLocalTFPlayer();
    if (!pLocalPlayer)
        return;
    
    // Extract charge start info
    float flChargeStartTime = msg.ReadFloat();
    int nChargeStartTick = msg.ReadLong();
    
    // Extract angle data entries
    int numEntries = msg.ReadByte();
    
    for (int i = 0; i < numEntries; i++)
    {
        float flClientTime = msg.ReadFloat();
        int nClientTick = msg.ReadLong();
        
        QAngle angles;
        angles[PITCH] = msg.ReadFloat();
        angles[YAW] = msg.ReadFloat();
        angles[ROLL] = msg.ReadFloat();
        
        // Process the angle data on server
        // Note: This is server->client message so we're just dumping the data
    }
}

//-----------------------------------------------------------------------------
// Purpose: Register our user message and hook it
//-----------------------------------------------------------------------------
CTFHudChargeData::CTFHudChargeData(const char *pElementName) : CHudElement(pElementName)
{
    // Register with the HUD system
    SetHiddenBits(HIDEHUD_MISCSTATUS);
    
    // Hook the message
    HOOK_MESSAGE(ChargeAngleData);
}

// Create an instance of the class
static CTFHudChargeData g_TFHudChargeData("CTFHudChargeData");
