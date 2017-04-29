#include "teacher.h"

Teacher::Teacher(std::vector<Schedule::session> in_allSessions, std::string in_name, Subject in_subject) :
	TimeScheduleEntity(in_allSessions), _name(in_name), _subject(in_subject)
{
}

bool Teacher::addOneHour(Slot* in_slot)
{
	if (_hourGiven == _nbHourToGive)
	{
		return false;
	}
	else
	{
		_hourGiven++;
		return true;
	}
}
