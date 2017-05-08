#ifndef TEACHER_H
#define TEACHER_H

#include <string>
#include <vector>
#include <set>
#include "IncludedHeaders.h"
#include "Calendar.h"
#include "TimeScheduleEntity.h"
class Class;

class Teacher : public TimeScheduleEntity
{
public:
	Teacher();
	Teacher(std::vector<Schedule::session> in_allSessions, std::string in_name, Subject in_subject);

	void addClass(Class* in_pClass);
	std::string getName() const;
	std::set<Class*> getClasses() const;
	Subject getSubject()  const;
	bool addOneHour(Slot* in_slot);

private:

	std::string _name = "DEFAULT";
	ul _nbHourToGive = 15;
	ul _hourGiven = 0;
	Subject _subject = Subject::EMPTY;
	std::set<Class*> _allClasses;
};



#endif // TEACHER_H