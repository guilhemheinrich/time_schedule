#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <set>
#include <string>
#include "IncludedHeaders.h"

enum class Day {MONDAY = 0, TUESDAY = 1, WEDNESDAY = 2, THURSDAY = 3, FRIDAY = 4, SUNDAY = 5};
std::string to_string(Day);

class Schedule
{
public:
    Schedule(){}
    Schedule(Day day, ul hour, ul minute);

	// Duration is in hour
    static const ul session_duration = 1;

	static std::set<int> buildRegularCalendar(std::set<Day> in_days = { Day::MONDAY,  Day::TUESDAY,  Day::WEDNESDAY,  Day::THURSDAY,  Day::FRIDAY,  Day::SUNDAY},
		std::pair<ul, ul> in_startMorning = std::pair<ul, ul>(8, 0), ul in_morningDuration = 4, std::pair<ul, ul> in_startAfternoon = std::pair<ul, ul>(14, 0), ul in_afternoonDuration = 4);

    ul encode() const;
    static Schedule decode(ul footprint);

	ul next();
	static ul next(ul);

	// For using shedule as Key
	bool operator==(Schedule in_rValue);
	bool operator<=(Schedule in_rValue);
	bool operator>=(Schedule in_rValue);
	bool operator<(Schedule in_rValue);
	bool operator>(Schedule in_rValue);



	Day getDay();
	ul getHour();
	ul getMinute();
private:
	ul _ID;
    Day _day = Day::MONDAY;
    ul _hour;
    ul _minute;

};

#endif // SCHEDULE_H
