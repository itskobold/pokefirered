#ifndef GUARD_TIME_H
#define GUARD_TIME_H

void StartGameTime(void);
void StopGameTime(void);
u8 Format12Hour(u8 hour);
u8 GetSimulatedMinutes(void);
u8 GetSunriseTime(void);
u8 GetSunsetTime(void);
u8 GetDayPeriod(void);
u8 IsDay(void);
void InitGameTime(void);
void IncrementSecond(void);
void IncrementMinute(void);
void IncrementHour(void);
void IncrementDay(void);
void IncrementMonth(void);
void IncrementYear(void);

#endif // GUARD_TIME_H