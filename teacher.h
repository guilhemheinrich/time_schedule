#ifndef TEACHER_H
#define TEACHER_H

#include <string>
#include <vector>
#include "IncludedHeaders.h"
#include "Calendar.h"
#include "TimeScheduleEntity.h"

class Teacher : public TimeScheduleEntity
{
public:
	Teacher();
	Teacher(std::vector<Schedule::session> in_allSessions, std::string in_name, Subject in_subject);

	bool addOneHour(Slot* in_slot);

private:

	std::string _name = "DEFAULT";
	ul _nbHourToGive = 15;
	ul _hourGiven = 0;
	Subject _subject = Subject::EMPTY;

};

#endif // TEACHER_H