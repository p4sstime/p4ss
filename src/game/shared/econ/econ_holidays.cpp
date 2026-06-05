//========= Copyright Valve Corporation, All rights reserved. ============//

#include "cbase.h"

#include "rtime.h"
#include "econ_holidays.h"

//-----------------------------------------------------------------------------
// Purpose: Interface that answers the simple question "on the passed-in time,
//			would this holiday be active?". Any caching of calculations is left
//			up to subclasses.
//-----------------------------------------------------------------------------
class IIsHolidayActive
{
public:
	IIsHolidayActive( const char *pszHolidayName ) : m_pszHolidayName( pszHolidayName ) { }
	virtual ~IIsHolidayActive ( ) { }
	virtual bool IsActive( const CRTime& timeCurrent ) = 0;

	const char *GetHolidayName() const { return m_pszHolidayName; }

private:
	const char *m_pszHolidayName;
};

//-----------------------------------------------------------------------------
// Purpose: Always-disabled. Dummy event needed to map to slot zero for "disabled
//			holiday".
//-----------------------------------------------------------------------------
class CNoHoliday : public IIsHolidayActive
{
public:
	CNoHoliday() : IIsHolidayActive( "none" ) { }

	virtual bool IsActive( const CRTime& timeCurrent )
	{
		return false;
	}
};

//-----------------------------------------------------------------------------
// Purpose: A holiday that lasts exactly one and only one day.
//-----------------------------------------------------------------------------
class CSingleDayHoliday : public IIsHolidayActive
{
public:
	CSingleDayHoliday( const char *pszName, int iMonth, int iDay )
		: IIsHolidayActive( pszName )
		, m_iMonth( iMonth )
		, m_iDay( iDay )
	{
		//
	}

	virtual bool IsActive( const CRTime& timeCurrent )
	{
		return m_iMonth == timeCurrent.GetMonth()
			&& m_iDay == timeCurrent.GetDayOfMonth();
	}

private:
	int m_iMonth;
	int m_iDay;
};

//-----------------------------------------------------------------------------
// Purpose: We want "week long" holidays to encompass at least two weekends,
//			so that players get plenty of time interacting with the holiday
//			features.
//-----------------------------------------------------------------------------
class CWeeksBasedHoliday : public IIsHolidayActive
{
public:
	CWeeksBasedHoliday( const char *pszName, int iMonth, int iDay, int iExtraWeeks )
		: IIsHolidayActive( pszName )
		, m_iMonth( iMonth )
		, m_iDay( iDay )
		, m_iExtraWeeks( iExtraWeeks )
		, m_iCachedCalculatedYear( 0 )
	{
		// We'll calculate the interval the first time we call IsActive().
	}

	void RecalculateTimeActiveInterval( int iYear )
	{
		// Get the date of the holiday.
		tm holiday_tm = { };
		holiday_tm.tm_mday = m_iDay;
		holiday_tm.tm_mon  = m_iMonth - 1;
		holiday_tm.tm_year = iYear - 1900; // convert to years since 1900
		mktime( &holiday_tm );

		// The event starts on the first Friday at least four days prior to the holiday.
		tm start_time_tm( holiday_tm );
		start_time_tm.tm_mday -= 4;							// Move back four days.
		mktime( &start_time_tm );
		int days_offset = start_time_tm.tm_wday - kFriday;	// Find the nearest prior Friday.
		if ( days_offset < 0 )
			days_offset += 7;
		start_time_tm.tm_mday -= days_offset;
		time_t start_time = mktime( &start_time_tm );

		// The event ends on the first Monday after the holiday, maybe plus some additional fudge
		// time.
		tm end_time_tm( holiday_tm );
		days_offset = 7 - (end_time_tm.tm_wday - kMonday);
		if ( days_offset >= 7 )
			days_offset -= 7;
		end_time_tm.tm_mday += days_offset + 7 * m_iExtraWeeks;
		time_t end_time = mktime( &end_time_tm );


		m_timeStart = start_time;
		m_timeEnd = end_time;

		// We're done and our interval data is cached.
		m_iCachedCalculatedYear = iYear;
	}

	virtual bool IsActive( const CRTime& timeCurrent )
	{
		const int iCurrentYear = timeCurrent.GetYear();
		if ( m_iCachedCalculatedYear != iCurrentYear )
			RecalculateTimeActiveInterval( iCurrentYear );

		return timeCurrent.GetRTime32() > m_timeStart
			&& timeCurrent.GetRTime32() < m_timeEnd;
	}

private:
	static const int kMonday = 1;
	static const int kFriday = 5;

	int m_iMonth;
	int m_iDay;
	int m_iExtraWeeks;
	
	// Filled out from RecalculateTimeActiveInterval().
	int m_iCachedCalculatedYear;

	RTime32 m_timeStart;
	RTime32 m_timeEnd;
};

//-----------------------------------------------------------------------------
// Purpose: A holiday that repeats on a certain time interval, like "every N days"
//			or "once every two months" or, uh, "any time there's a full moon".
//-----------------------------------------------------------------------------
class CCyclicalHoliday : public IIsHolidayActive
{
public:
	CCyclicalHoliday( const char *pszName, int iMonth, int iDay, int iYear, float fCycleLengthInDays, float fBonusTimeInDays )
		: IIsHolidayActive( pszName )
		, m_fCycleLengthInDays( fCycleLengthInDays )
		, m_fBonusTimeInDays( fBonusTimeInDays )
	{
		// When is our initial interval?
		tm holiday_tm = { };
		holiday_tm.tm_mday = iDay;
		holiday_tm.tm_mon  = iMonth - 1;
		holiday_tm.tm_year = iYear - 1900; // convert to years since 1900
		m_timeInitial = mktime( &holiday_tm );
	}

	virtual bool IsActive( const CRTime& timeCurrent )
	{
		// Days-to-seconds conversion.
		const int iSecondsPerDay = 24 * 60 * 60;

		// Convert our cycle/buffer times to seconds.
		const int iCycleLengthInSeconds = (int)(m_fCycleLengthInDays * iSecondsPerDay);
		const int iBufferTimeInSeconds  = (int)(m_fBonusTimeInDays * iSecondsPerDay);

		// How long has it been since we started this cycle?
		int iSecondsIntoCycle = (timeCurrent.GetRTime32() - m_timeInitial) % iCycleLengthInSeconds;

		// If we're within the buffer period right after the start of a cycle, we're active.
		if ( iSecondsIntoCycle < iBufferTimeInSeconds )
			return true;

		// If we're within the buffer period towards the end of a cycle, we're active.
		if ( iSecondsIntoCycle > iCycleLengthInSeconds - iBufferTimeInSeconds )
			return true;

		// Alas, normal mode for us.
		return false;
	}

private:
	time_t m_timeInitial ;

	float m_fCycleLengthInDays;
	float m_fBonusTimeInDays;
};

//-----------------------------------------------------------------------------
// Purpose: A pseudo-holiday that is active when either of its child holidays
//			is active. Works through pointers but does not manage memory.
//-----------------------------------------------------------------------------
class COrHoliday : public IIsHolidayActive
{
public:
	COrHoliday( const char *pszName, IIsHolidayActive *pA, IIsHolidayActive *pB )
		: IIsHolidayActive( pszName )
		, m_pA( pA )
		, m_pB( pB )
	{
		Assert( pA );
		Assert( pB );
		Assert( pA != pB );
	}

	virtual bool IsActive( const CRTime& timeCurrent )
	{
		return m_pA->IsActive( timeCurrent )
			|| m_pB->IsActive( timeCurrent );
	}

private:
	IIsHolidayActive *m_pA;
	IIsHolidayActive *m_pB;
};

//-----------------------------------------------------------------------------
// Purpose: Holiday that is defined by a start and end date
//-----------------------------------------------------------------------------
class CDateBasedHoliday : public IIsHolidayActive
{
public:
	CDateBasedHoliday( const char *pszName, const char *pszStartTime, const char *pszEndTime )
		: IIsHolidayActive( pszName )
	{
		m_rtStartTime =	 CRTime::RTime32FromString( pszStartTime );
		m_rtEndTime = CRTime::RTime32FromString( pszEndTime );
	}

	virtual bool IsActive( const CRTime& timeCurrent )
	{
		return ( ( timeCurrent >= m_rtStartTime ) && ( timeCurrent <= m_rtEndTime ) );
	}

	RTime32 GetEndRTime() const
	{
		return m_rtEndTime.GetRTime32();
	}


private:
	CRTime m_rtStartTime;
	CRTime m_rtEndTime;
};

//-----------------------------------------------------------------------------
// Purpose: Holiday that is defined by a start and end date with no year specified
//-----------------------------------------------------------------------------
class CDateBasedHolidayNoSpecificYear : public IIsHolidayActive
{
public:
	CDateBasedHolidayNoSpecificYear( const char *pszName, const char *pszStartTime, const char *pszEndTime )
		: IIsHolidayActive( pszName )
		, m_pszStartTime( pszStartTime )
		, m_pszEndTime( pszEndTime )
		, m_iCachedYear( -1 )
	{
	}

	virtual bool IsActive( const CRTime& timeCurrent )
	{
		const int iYear = timeCurrent.GetYear();

		if ( iYear != m_iCachedYear )
		{
			char m_szStartTime[k_RTimeRenderBufferSize];
			char m_szEndTime[k_RTimeRenderBufferSize];

			V_sprintf_safe( m_szStartTime, "%d-%s", iYear, m_pszStartTime );
			V_sprintf_safe( m_szEndTime, "%d-%s", iYear, m_pszEndTime );

			m_iCachedYear = iYear;
			m_rtCachedStartTime = CRTime::RTime32FromString( m_szStartTime );
			m_rtCachedEndTime = CRTime::RTime32FromString( m_szEndTime );
		}

		return ( ( timeCurrent >= m_rtCachedStartTime ) && ( timeCurrent <= m_rtCachedEndTime ) );
	}

	RTime32 GetEndRTime() const
	{
		return m_rtCachedEndTime.GetRTime32();
	}

private:
	const char *m_pszStartTime;
	const char *m_pszEndTime;

	int m_iCachedYear;
	CRTime m_rtCachedStartTime;
	CRTime m_rtCachedEndTime;
};

//-----------------------------------------------------------------------------
// Purpose: Actual holiday implementation objects.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
bool EconHolidays_IsHolidayActive( int iHolidayIndex, const CRTime& timeCurrent )
{
	return false;
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
int	EconHolidays_GetHolidayForString( const char* pszHolidayName )
{
	return 0;
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
const char *EconHolidays_GetActiveHolidayString()
{
	// No holidays currently active.
	return NULL;
}