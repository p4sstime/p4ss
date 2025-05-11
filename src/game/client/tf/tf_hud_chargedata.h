//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Header for charge angle data handling
//
//=============================================================================

#ifndef TF_HUD_CHARGEDATA_H
#define TF_HUD_CHARGEDATA_H
#ifdef _WIN32
#pragma once
#endif

#include "hudelement.h"

//-----------------------------------------------------------------------------
// Purpose: Handles charge angle data user messages
//-----------------------------------------------------------------------------
class CTFHudChargeData : public CHudElement
{
public:
    CTFHudChargeData(const char *pElementName);
};

// Message handler function
void __MsgFunc_ChargeAngleData(bf_read &msg);

#endif // TF_HUD_CHARGEDATA_H
