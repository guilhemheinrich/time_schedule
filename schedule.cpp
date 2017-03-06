#include "schedule.h"
#include <vector>

namespace Schedule
{

	void buildAllTimeSlots()
	{
		for (ul ulDayCpt = 0; ulDayCpt < 6; ulDayCpt++)
		{
			day tmpDay = week[ulDayCpt];
			time_slot tmpTs;
			for (ul ulMorning = 0; ulMorning < tmpDay.nb_session_morning; ulMorning++)
			{
				// root + week day + startMorning + ulMorning * durationSession
				tmpTs.start = root_day;
				tmpTs.start.tm_hour += tmpDay.start_morning;
				tmpTs.start.tm_hour += ulMorning * session_duration;

				tmpTs.end.tm_hour = tmpTs.start.tm_hour + session_duration;
				allTimeSlot.push_back(tmpTs);
			}

			for (ul ulAfternoon = 0; ulAfternoon < tmpDay.nb_session_morning; ulAfternoon++)
			{
				// root + week day + startAfternoon + ulAfternoon * durationSession
				tmpTs.start = root_day;
				tmpTs.start.tm_hour += tmpDay.start_morning;
				tmpTs.start.tm_hour += ulAfternoon * session_duration;

				tmpTs.end.tm_hour = tmpTs.start.tm_hour + session_duration;
				allTimeSlot.push_back(tmpTs);
			}
		}
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
