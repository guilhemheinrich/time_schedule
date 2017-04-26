#include "teacher.h"


Teacher::Teacher(std::string in_name) :
	_name(in_name)
{
}

Teacher::Teacher(std::string in_name, Subject in_subject) :
	_name(in_name), _subject(in_subject)
{
}

bool Teacher::addOneHour()
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
