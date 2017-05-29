#include "schedule.h"
#include <vector>
#include <set>

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

	std::set<time_slot> buildAllTimeSlots(std::vector<session> in_session_template)
	{
		std::set<time_slot> out_sTimeSlots;
		for (session sessionTmp : in_session_template)
		{
			time_slot tmpTs;


			for (ul ulCpt = 0; ulCpt < sessionTmp.hourDuration(); ulCpt++)
			{
				// Keep track of the session for further identification
				tmpTs.session = sessionTmp;

				// root + week day + startMorning + ulMorning * durationSession
				tmpTs.start = sessionTmp.start();

				//tmpTs.start.tm_hour += tmpDay.start;
				tmpTs.start.tm_hour += ulCpt;

				tmpTs.end = tmpTs.start;
				tmpTs.end.tm_hour = tmpTs.start.tm_hour + 1;
				out_sTimeSlots.insert(tmpTs);
			}
		}
		return out_sTimeSlots;
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

	time_slot & time_slot::operator++()
	{
		// TODO: insérer une instruction return ici
		start.tm_hour++;
		end.tm_hour++;
		return *this;
	}

	time_slot time_slot::operator++(int)
	{
		time_slot result(*this);	// make a copy for result
		++(*this);					// Now use the prefix version to do the work
		return result;
	}

	time_slot & time_slot::operator--()
	{
		// TODO: insérer une instruction return ici
		start.tm_hour--;
		end.tm_hour--;
		return *this;
	}

	time_slot time_slot::operator--(int)
	{
		time_slot result(*this);	// make a copy for result
		--(*this);					// Now use the prefix version to do the work
		return result;
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

	session::session()
	{
		_ID ="DEFAULT";

	}

	session::session(tm in_start, ul in_hourDuration):
		_start(in_start), _hourDuration(in_hourDuration)
	{ 
		_ID = std::to_string(in_start.tm_year) + "_" + std::to_string(in_start.tm_yday) + "_" + std::to_string(in_start.tm_hour) + "x" + std::to_string(in_hourDuration);

		for (ul ulCpt = 0; ulCpt < in_hourDuration; ulCpt++)
		{
			time_slot tmpTm;

			tmpTm.start = in_start;
			tmpTm.start.tm_hour += ulCpt;

			tmpTm.end = tmpTm.start;
			tmpTm.end.tm_hour++;
			_allTimeSlots.insert(tmpTm);
		}
	}

	tm session::start() const
	{
		return _start;
	}

	ul session::hourDuration() const
	{
		return _hourDuration;
	}

	std::set<time_slot>::iterator session::begin()
	{
		return _allTimeSlots.begin();
	}

	std::set<time_slot>::iterator session::end()
	{
		return _allTimeSlots.end();
	}

	std::set<time_slot>::const_iterator session::begin() const
	{
		return _allTimeSlots.begin();
	}

	std::set<time_slot>::const_iterator session::end() const
	{
		return _allTimeSlots.end();
	}

	bool operator==(const session &in_lValue, const session &in_rValue)
	{
		if (in_lValue._ID == in_rValue._ID)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator<=(const session &in_lValue, const session  &in_rValue)
	{
		return in_lValue._ID <= in_rValue._ID;
	}

	bool operator>=(const session &in_lValue, const session  &in_rValue)
	{
		return in_lValue._ID >= in_rValue._ID;
	}

	bool operator<(const session &in_lValue, const session &in_rValue)
	{
		return !(in_lValue >= in_rValue);
	}

	bool operator>(const session &in_lValue, const session &in_rValue)
	{
		return !(in_lValue <= in_rValue);
	}

	//template<>
	//std::map<time_slot, Slot*>::iterator SessionPrototype<Slot>::begin()
	//{
	//	return _content.begin();
	//}

	//template<>
	//std::map<time_slot, Slot*>::iterator SessionPrototype<Slot>::end()
	//{
	//	return _content.end();
	//}

	//template<>
	//std::map<time_slot, Slot*>::const_iterator SessionPrototype<Slot>::begin() const
	//{
	//	return _content.begin();
	//}

	//template<>
	//std::map<time_slot, Slot*>::const_iterator SessionPrototype<Slot>::end() const
	//{
	//	return _content.end();
	//}
}
