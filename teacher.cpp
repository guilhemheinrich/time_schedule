#include "teacher.h"
#include "class.h"

Teacher::Teacher()
{
}

Teacher::Teacher(std::vector<Schedule::session> in_allSessions, std::string in_name, Subject in_subject) :
	TimeScheduleEntity(in_allSessions), _name(in_name), _subject(in_subject)
{
}

void Teacher::addClass(Class * in_pClass)
{
	if (in_pClass->getTeachers().count(this->_subject) == 0)
	{
		in_pClass->setTeacherForSubject(_subject, this);
	}
	_allClasses.insert(in_pClass);
}

std::string Teacher::getName() const
{
	return _name;
}

std::set<Class*> Teacher::getClasses() const
{
	return _allClasses;
}

Subject Teacher::getSubject() const
{
	return _subject;
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
		add(in_slot);
		return true;
	}
}
