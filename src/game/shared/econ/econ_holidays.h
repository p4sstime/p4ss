//========= Copyright Valve Corporation, All rights reserved. ============//

#ifndef ECON_HOLIDAYS_H
#define ECON_HOLIDAYS_H

#ifdef _WIN32
#pragma once
#endif

bool EconHolidays_IsHolidayActive( int iHolidayIndex, const class CRTime& timeCurrent );
int	EconHolidays_GetHolidayForString( const char* pszHolidayName );
const char *EconHolidays_GetActiveHolidayString();

#endif // ECON_HOLIDAYS_H
