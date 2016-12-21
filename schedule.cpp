#include "schedule.h"
#include <vector>


Schedule::Schedule(Day day, ul hour, ul minute):
_day(day)
{
    if (hour < 24 && minute <61)
    {
        _hour = hour;
        _minute = minute;
    }
	_ID = encode();
}

std::set<int> Schedule::buildRegularCalendar(std::set<Day> in_days, std::pair<ul, ul> in_startMorning, ul in_morningDuration, std::pair<ul, ul> in_startAfternoon, ul in_afternoonDuration)
{
	std::set<int> out_scheduleIDs;
	for (Day day : in_days)
	{
		for (ul morningCpt = 0; morningCpt < in_morningDuration; morningCpt++)
		{
			Schedule tmp_schedule(day, in_startMorning.first + morningCpt * session_duration, in_startMorning.second);
			out_scheduleIDs.insert(tmp_schedule._ID);
		}

		for (ul afternoonCpt = 0; afternoonCpt < in_afternoonDuration; afternoonCpt++)
		{
			Schedule tmp_schedule(day, in_startAfternoon.first + afternoonCpt * session_duration, in_startAfternoon.second);
			out_scheduleIDs.insert(tmp_schedule._ID);
		}
	}

	return out_scheduleIDs;
}


int Schedule::encode() const
{
    int out_footprint = 0;
    out_footprint += (int) _day * 24 * 60;
    out_footprint += (int) _hour * 60;
    out_footprint += (int) _minute;
    return out_footprint;
}

Schedule Schedule::decode(int footprint)
{  
    ul ulTmp = footprint % (24 * 60);
    ul minute = footprint % 60;
	ul hour = (ulTmp - minute) / 60;
    Day day = (Day) (footprint / (24 * 60));
	Schedule out_schedule(day, hour, minute);
	return out_schedule;
}

int Schedule::next()
{
	return next(_ID);
}

int Schedule::next(int in_ID)
{
	return in_ID + session_duration * 60;
}

Day Schedule::getDay()
{
	return _day;
}

ul Schedule::getHour()
{
	return _hour;
}

ul Schedule::getMinute()
{
	return _minute;
}

std::string to_string(Day in_day)
{
	static std::string DayName[6] = { "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SUNDAY" };
	return DayName[(int)in_day];
}
