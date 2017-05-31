#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <set>
#include <string>
#include <ctime>
#include <vector>
#include <map>
#include <iterator>
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
	struct time_slot;
	class session;

	template<typename TYPE>
	class SessionPrototype;
	// First day of the year
	static tm root_day;

	void initalizeRootDay(tm in_rootDay);
	// duration of a session (time slot), in hour
	//static int session_duration = 1;

	// struct carrying time schedule of a session
	class session
	{
	public:
		session();
		session(tm in_tmStart, ul in_ulHourDuration);

		tm start() const;
		ul hourDuration() const;
		std::string id() const;

		friend bool operator==(const session &in_lValue, const session &in_rValue);
		friend bool operator<=(const session &in_lValue, const session &in_rValue);
		friend bool operator>=(const session &in_lValue, const session &in_rValue);
		friend bool operator<(const session &in_lValue, const session &in_rValue);
		friend bool operator>(const session &in_lValue, const session &in_rValue);

		std::set<time_slot>::iterator begin();
		std::set<time_slot>::iterator end();

		std::set<time_slot>::const_iterator begin() const;
		std::set<time_slot>::const_iterator end() const;
	private:
		tm _start;
		ul _hourDuration = 8;
		std::set<time_slot> _allTimeSlots;
		std::string _ID;
	};

	bool operator==(const session &in_lValue, const session &in_rValue);
	bool operator<=(const session &in_lValue, const session &in_rValue);
	bool operator>=(const session &in_lValue, const session &in_rValue);
	bool operator<(const session &in_lValue, const session &in_rValue);
	bool operator>(const session &in_lValue, const session &in_rValue);

	template<typename TYPE>
	class SessionPrototype
	{
		friend class session;

		//friend std::map<time_slot, TYPE*>::const_iterator begin(SessionPrototype<TYPE> &in_sessionPrototype);
		//friend std::map<time_slot, TYPE*>::const_iterator end(SessionPrototype<TYPE> &in_sessionPrototype);
		//friend std::map<time_slot, TYPE*>::iterator begin(SessionPrototype<TYPE> &in_sessionPrototype);
		//friend std::map<time_slot, TYPE*>::iterator end(SessionPrototype<TYPE> &in_sessionPrototype);
	public:
		SessionPrototype();
		SessionPrototype(session in_session, TYPE in_defaultInitializer);
		SessionPrototype(const SessionPrototype<TYPE> &in_sessionPrototype);

		void at(time_slot in_timeSlot, TYPE in_newValue);
		const ul size() const;
		const TYPE& operator[](time_slot in_timeSlot) const;
		TYPE& operator[](time_slot in_timeSlot);

		const std::map<time_slot, TYPE > getContent() const;
		std::map<time_slot, TYPE > getContent();
		std::map<time_slot, TYPE >* getPointerContent();


		//std::map<time_slot, TYPE*>::iterator begin();
		//std::map<time_slot, TYPE*>::iterator end();

		//std::map<time_slot, TYPE*>::const_iterator begin() const;
		//std::map<time_slot, TYPE*>::const_iterator end() const;


		operator std::string();
	private:
		std::map<time_slot, TYPE> _content;
		session _session;
	};



	// struct carrying time slot
	struct time_slot
	{
		session session;
		tm start;
		tm end;

		const double _encode() const;

		time_slot& operator++(); // prefix operator
		time_slot operator++(int); // postfix operator


		time_slot& operator--(); // prefix operator
		time_slot operator--(int); // postfix operator

	private:
		// used internally to compare time slot
	};

	bool operator==(const time_slot &in_lValue, const time_slot &in_rValue);
	bool operator<=(const time_slot &in_lValue, const time_slot &in_rValue);
	bool operator>=(const time_slot &in_lValue, const time_slot &in_rValue);
	bool operator<(const time_slot &in_lValue, const time_slot &in_rValue);
	bool operator>(const time_slot &in_lValue, const time_slot &in_rValue);


	std::set<time_slot> buildAllTimeSlots(std::vector<session> in_session_template);

	int encode(tm timeToEncode);
	bool checkInTimeInterval(tm timeToCheck, tm start, tm end);

	//template<typename TYPE>
	//inline std::map<time_slot, TYPE*>::iterator SessionPrototype<TYPE>::begin()
	//{
	//	return _content.begin();
	//}

	//template<typename TYPE>
	//inline std::map<time_slot, TYPE*>::iterator SessionPrototype<TYPE>::end()
	//{
	//	return _content.end();
	//}

	//template<typename TYPE>
	//inline std::map<time_slot, TYPE*>::const_iterator SessionPrototype<TYPE>::begin() const
	//{
	//	return _content.begin();
	//}

	//template<typename TYPE>
	//inline std::map<time_slot, TYPE*>::const_iterator SessionPrototype<TYPE>::end() const
	//{
	//	return _content.end();
	//}

	//template<typename TYPE>
	//inline std::map<time_slot, TYPE*>::iterator begin(SessionPrototype<TYPE> &in_sessionPrototype)
	//{
	//	return in_sessionPrototype._content.begin();
	//}

	//template<typename TYPE>
	//inline std::map<time_slot, TYPE*>::iterator end(SessionPrototype<TYPE> &in_sessionPrototype)
	//{
	//	return in_sessionPrototype._content.end();
	//}

	//template<typename TYPE>
	//inline std::map<time_slot, TYPE*>::const_iterator begin(SessionPrototype<TYPE> &in_sessionPrototype)
	//{
	//	return in_sessionPrototype._content.begin();
	//}

	//template<typename TYPE>
	//inline std::map<time_slot, TYPE*>::const_iterator end(SessionPrototype<TYPE> &in_sessionPrototype)
	//{
	//	return in_sessionPrototype._content.end();
	//}

	template<typename TYPE>
	inline SessionPrototype<TYPE>::SessionPrototype()
	{
	}

	template<typename TYPE>
	inline SessionPrototype<TYPE>::SessionPrototype(session in_session, TYPE in_defaultInitializer):
		_session(in_session)
	{
		for (ul ulCpt = 0; ulCpt < in_session.hourDuration(); ulCpt++)
		{
			time_slot tmpTm;

			tmpTm.start = in_session.start();
			tmpTm.start.tm_hour += ulCpt;

			tmpTm.end = tmpTm.start;
			tmpTm.end.tm_hour++;

			_content[tmpTm] = in_defaultInitializer;
		}
	}

	template<typename TYPE>
	inline SessionPrototype<TYPE>::SessionPrototype(const SessionPrototype<TYPE> &in_sessionPrototype):
		_session(in_sessionPrototype._session), _content(in_sessionPrototype._content)
	{
	}
	template<typename TYPE>
	inline void SessionPrototype<TYPE>::at(time_slot in_timeSlot, TYPE in_newValue)
	{
		_content[in_timeSlot] = in_newValue;
	}

	template<typename TYPE>
	inline const ul SessionPrototype<TYPE>::size() const
	{
		return _content.size();
	}

	template<typename TYPE>
	inline const TYPE& SessionPrototype<TYPE>::operator[](time_slot in_timeSlot) const
	{
		return _content.at(in_timeSlot);
	}

	template<typename TYPE>
	inline TYPE& SessionPrototype<TYPE>::operator[](time_slot in_timeSlot)
	{
		return _content[in_timeSlot];
	}

	template<typename TYPE>
	inline const std::map<time_slot, TYPE> SessionPrototype<TYPE>::getContent() const
	{
		return _content;
	}

	template<typename TYPE>
	inline std::map<time_slot, TYPE> SessionPrototype<TYPE>::getContent()
	{
		return _content;
	}

	template<typename TYPE>
	inline std::map<time_slot, TYPE>* SessionPrototype<TYPE>::getPointerContent()
	{
		return &_content;
	}



	template<typename TYPE>
	inline SessionPrototype<TYPE>::operator std::string()
	{
		return _session._ID
	}


}



#endif // SCHEDULE_H
