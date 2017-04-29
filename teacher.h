#ifndef TEACHER_H
#define TEACHER_H

#include <string>
#include <vector>
#include "IncludedHeaders.h"
#include "Calendar.h"
#include "TimeScheduleEntity.h"

class Teacher : TimeScheduleEntity
{
public:

	Teacher(std::vector<Schedule::session> in_allSessions, std::string in_name, Subject in_subject);

	bool addOneHour(Slot* in_slot);

private:

	std::string _name;
	ul _nbHourToGive = 15;
	ul _hourGiven = 0;
	Subject _subject;

};

#endif // TEACHER_H