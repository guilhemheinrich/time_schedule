#include "schedule.h"
#include <vector>

namespace Schedule
{
	void initalizeRootDay(tm in_rootDay)
	{
		root_day.tm_sec = in_rootDay.tm_sec;   // seconds of minutes from 0 to 61
		root_day.tm_min = in_rootDay.tm_min;   // minutes of hour from 0 to 59
		root_day.tm_hour = in_rootDay.tm_hour;  // hours of day from 0 to 24
		root_day.tm_mday = in_rootDay.tm_mday;  // day of month from 1 to 31
		root_day.tm_mon = in_rootDay.tm_mon;   // month of year from 0 to 11
		root_day.tm_year = in_rootDay.tm_year;  // year since 1900
		root_day.tm_wday = in_rootDay.tm_wday;  // days since sunday
		root_day.tm_yday = in_rootDay.tm_yday;  // days since January 1st
		root_day.tm_isdst = in_rootDay.tm_isdst;
	}

	std::vector<time_slot> buildAllTimeSlots()
	{
		std::vector<time_slot> out_vTimeSlots;
		for (ul ulDayCpt = 0; ulDayCpt < 6; ulDayCpt++)
		{
			session tmpDay = week[ulDayCpt];
			time_slot tmpTs;
			//for (ul ulMorning = 0; ulMorning < tmpDay.nb_session_morning; ulMorning++)
			//{
			//	// root + week day + startMorning + ulMorning * durationSession
			//	tmpTs.start = root_day;
			//	tmpTs.start.tm_hour += tmpDay.start_morning;
			//	tmpTs.start.tm_hour += ulMorning * session_duration;

			//	tmpTs.end = tmpTs.start;
			//	tmpTs.end.tm_hour = tmpTs.start.tm_hour + session_duration;
			//	out_vTimeSlots.push_back(tmpTs);
			//}

			//for (ul ulAfternoon = 0; ulAfternoon < tmpDay.nb_session_morning; ulAfternoon++)
			//{
			//	// root + week day + startAfternoon + ulAfternoon * durationSession
			//	tmpTs.start = root_day;
			//	tmpTs.start.tm_hour += tmpDay.start_afternoon;
			//	tmpTs.start.tm_hour += ulAfternoon * session_duration;

			//	tmpTs.end.tm_hour = tmpTs.start.tm_hour + session_duration;
			//	out_vTimeSlots.push_back(tmpTs);
			//}

			for (ul ulCpt = 0; ulCpt < tmpDay.hourDuration; ulCpt++)
			{
				// root + week day + startMorning + ulMorning * durationSession
				tmpTs.start = tmpDay.start;
				tmpTs.start.tm_yday = tmpDay.start.tm_yday + ulDayCpt;
				tmpTs.start.tm_mday = tmpDay.start.tm_mday + ulDayCpt;
				tmpTs.start.tm_wday = tmpDay.start.tm_wday + ulDayCpt;
				//tmpTs.start.tm_hour += tmpDay.start;
				tmpTs.start.tm_hour += ulCpt;

				tmpTs.end = tmpTs.start;
				tmpTs.end.tm_hour = tmpTs.start.tm_hour + 1;
				out_vTimeSlots.push_back(tmpTs);
			}
		}
		return out_vTimeSlots;
	}



	int encode(tm timeToEncode)
	{
		int out_value;
		out_value = timeToEncode.tm_yday * 24 * 60;
		out_value += timeToEncode.tm_hour * 60;
		out_value += timeToEncode.tm_min;
		return out_value;
	}


	const double time_slot::_encode() const
	{
		double encoded = encode(start) + encode(end);
		encoded *= 0.5;
		return encoded;
	}



	bool operator==(const time_slot &in_lValue, const time_slot &in_rValue)
	{
		if (in_lValue.start.tm_yday == in_rValue.start.tm_yday &&
			in_lValue.start.tm_hour == in_rValue.start.tm_hour &&
			in_lValue.start.tm_min == in_rValue.start.tm_min &&
			in_lValue.end.tm_yday == in_rValue.end.tm_yday &&
			in_lValue.end.tm_hour == in_rValue.end.tm_hour &&
			in_lValue.end.tm_min == in_rValue.end.tm_min)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator<=(const time_slot &in_lValue, const time_slot  &in_rValue)
	{
		return in_lValue._encode() <= in_rValue._encode();
	}

	bool operator>=(const time_slot &in_lValue, const time_slot  &in_rValue)
	{
		return in_lValue._encode() >= in_rValue._encode();
	}

	bool operator<(const time_slot &in_lValue, const time_slot &in_rValue)
	{
		return !(in_lValue >= in_rValue);
	}

	bool operator>(const time_slot &in_lValue, const time_slot &in_rValue)
	{
		return !(in_lValue <= in_rValue);
	}
}
