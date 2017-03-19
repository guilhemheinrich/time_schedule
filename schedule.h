#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <set>
#include <string>
#include <ctime>
#include <vector>
#include "IncludedHeaders.h"

// test de ctime
//tm testtm;
//testtm.tm_sec = 1;   // seconds of minutes from 0 to 61
//testtm.tm_min = 0;   // minutes of hour from 0 to 59
//testtm.tm_hour = 0;  // hours of day from 0 to 24
//testtm.tm_mday = 1;  // day of month from 1 to 31
//testtm.tm_mon = 1;   // month of year from 0 to 11
//testtm.tm_year = 1;  // year since 1900
//testtm.tm_wday = 2;  // days since sunday
//testtm.tm_yday = 1;  // days since January 1st
//testtm.tm_isdst = 1; // hours of daylight savings time
namespace Schedule
{
	// First day of the year
	static tm root_day;

	void initalizeRootDay(tm in_rootDay);
	// duration of a session (time slot), in hour
	//static int session_duration = 1;

	// struct carrying time schedule of a session
	struct session
	{
		//int start_morning = 8;
		//ul nb_session_morning = 4;
		//int start_afternoon = 13;
		//ul nb_session_afternoon = 4;
		int start = 8;
		int end = 18;
	};

	// representation of a week as a time schedule
	static session week[6];

	// struct carrying time slot
	struct time_slot
	{
		tm start;
		tm end;

		const double _encode() const;
	private:
		// used internally to compare time slot
	};

	bool operator==(const time_slot &in_lValue, const time_slot &in_rValue);
	bool operator<=(const time_slot &in_lValue, const time_slot &in_rValue);
	bool operator>=(const time_slot &in_lValue, const time_slot &in_rValue);
	bool operator<(const time_slot &in_lValue, const time_slot &in_rValue);
	bool operator>(const time_slot &in_lValue, const time_slot &in_rValue);


	std::vector<time_slot> buildAllTimeSlots();

	int encode(tm timeToEncode);
	bool checkInTimeInterval(tm timeToCheck, tm start, tm end);
}

#endif // SCHEDULE_H
