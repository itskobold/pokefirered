#include "global.h"
#include "time.h"
#include "random.h"
#include "constants/time.h"

static const u8 sNumDaysPerMonth[MAX_MONTHS] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static const s8 sSunriseOffset[MAX_MONTHS] = {2, 1, 0, -1, -2, -3, -2, -1, 0, 1, 2, 3};
static const s8 sSunsetOffset[MAX_MONTHS] = {-2, -1, 0, 1, 2, 3, 2, 1, 0, -1, -2, -3};
static const u8 sSunriseTime = 7;  // 7am in March/September
static const u8 sSunsetTime = 19;  // 7pm in March/September

static u8 GetNumberOfDaysForMonth(u8 month, u8 year);
static void IncrementDayOfWeek(void);

void StartGameTime()
{
	gSaveBlock2Ptr->time.flowing = TRUE;
}

void StopGameTime()
{
	gSaveBlock2Ptr->time.flowing = FALSE;
}

u8 Format12Hour(u8 hour)
{
	if (hour == 0)
		return 12;
	if (hour > 12)
		hour -= 12;
	return hour;
}

u8 GetSimulatedMinutes()
{
	u16 secsMins = (gSaveBlock2Ptr->time.numMinutes * MAX_SECONDS) + gSaveBlock2Ptr->time.numSeconds;
	return secsMins / MAX_MINUTES;
}

u8 GetSunriseTime()
{
	return sSunriseTime + sSunriseOffset[gSaveBlock2Ptr->time.numMonths];
}

u8 GetSunsetTime()
{
	return sSunsetTime + sSunsetOffset[gSaveBlock2Ptr->time.numMonths];
}

u8 GetDayPeriod()
{
	u8 hour = gSaveBlock2Ptr->time.numHours;

	if (hour == 0)
		return DN_MIDNIGHT;
	else if (hour == 12)
		return DN_MIDDAY;

	u8 sunrise = GetSunriseTime();
	u8 sunset = GetSunsetTime();

	if (hour == sunrise || hour + 1 == sunrise)
		return DN_DAWN;
	else if (hour == sunset || hour + 1 == sunset)
		return DN_DUSK;
	else if (hour < sunset && hour > sunrise)
		return DN_DAY;
	else
		return DN_NIGHT;
}

u8 IsDay()
{
	u8 hour = gSaveBlock2Ptr->time.numHours;
	u8 sunrise = GetSunriseTime();
	u8 sunset = GetSunsetTime();

	if (hour < sunset && hour > sunrise)
		return TRUE;
	else
		return FALSE;
}

static u8 GetNumberOfDaysForMonth(u8 month, u8 year)
{
	// Leap year: if year % 4 == 0
	if (month == MONTH_FEBRUARY && year % 4 == 0)
		return sNumDaysPerMonth[MONTH_FEBRUARY] + 1;
	return sNumDaysPerMonth[month];
}

void InitGameTime()
{
	// Game begins at:
	// 9am, Tuesday, March 10th (random year)

	gSaveBlock2Ptr->time.numSeconds = 0;
	gSaveBlock2Ptr->time.numMinutes = 0;
	gSaveBlock2Ptr->time.numHours = 9;
	gSaveBlock2Ptr->time.numDays = 10;
	gSaveBlock2Ptr->time.numMonths = MONTH_MARCH;
	gSaveBlock2Ptr->time.numYears = Random() % MAX_YEARS;
	gSaveBlock2Ptr->time.day = DAY_TUESDAY;
}

void IncrementSecond()
{
	u8 second = gSaveBlock2Ptr->time.numSeconds + 1;
	if (second >= MAX_SECONDS)
	{
		gSaveBlock2Ptr->time.numSeconds = 0;
		IncrementMinute();
	}
	else
		gSaveBlock2Ptr->time.numSeconds = second;
}

void IncrementMinute()
{
	u8 minute = gSaveBlock2Ptr->time.numMinutes + 1;
	if (minute >= MAX_MINUTES)
	{
		gSaveBlock2Ptr->time.numMinutes = 0;
		IncrementHour();
	}
	else
		gSaveBlock2Ptr->time.numMinutes = minute;
}

void IncrementHour()
{
	u8 hour = gSaveBlock2Ptr->time.numHours + 1;
	if (hour >= MAX_HOURS)
	{
		gSaveBlock2Ptr->time.numHours = 0;
		IncrementDay();
	}
	else
		gSaveBlock2Ptr->time.numHours = hour;
}

void IncrementDay()
{
	u8 day = gSaveBlock2Ptr->time.numDays + 1;
	IncrementDayOfWeek();
	
	if (day >= GetNumberOfDaysForMonth(gSaveBlock2Ptr->time.numMonths, gSaveBlock2Ptr->time.numYears))
	{
		gSaveBlock2Ptr->time.numDays = 0;
		IncrementMonth();
	}
	else
		gSaveBlock2Ptr->time.numDays = day;
}

static void IncrementDayOfWeek()
{
	u8 day = gSaveBlock2Ptr->time.day + 1;

	if (day >= MAX_DAYS_OF_WEEK)
		gSaveBlock2Ptr->time.day = 0;
	else
		gSaveBlock2Ptr->time.day = day;
}

void IncrementMonth()
{
	u8 month = gSaveBlock2Ptr->time.numMonths + 1;
	if (month >= MAX_MONTHS)
	{
		gSaveBlock2Ptr->time.numMonths = 0;
		IncrementYear();
	}
	else
		gSaveBlock2Ptr->time.numMonths = month;
}

void IncrementYear()
{
	u8 year = gSaveBlock2Ptr->time.numHours + 1;
	if (year >= MAX_YEARS)
		gSaveBlock2Ptr->time.numYears = 0;
	else
		gSaveBlock2Ptr->time.numHours = year;
}
