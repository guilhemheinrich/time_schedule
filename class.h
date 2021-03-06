#ifndef CLASS_H
#define CLASS_H
#include <string>
#include <vector>
#include <map>
#include <functional>
#include "IncludedHeaders.h"
#include "teacher.h"
#include "TimeScheduleEntity.h"

struct hourObjectiveAndFill
{
	ul objective;
	ul fill = 0;
};

class Class : public TimeScheduleEntity
{
	friend bool operator==(const Class &in_lValue, const Class &in_rValue);
	friend bool operator<=(const Class &in_lValue, const Class &in_rValue);
	friend bool operator>=(const Class &in_lValue, const Class &in_rValue);
	friend bool operator<(const Class &in_lValue, const Class &in_rValue);
	friend bool operator>(const Class &in_lValue, const Class &in_rValue);
public:
	Class(std::vector<Schedule::session> in_allSessions, std::string in_name, std::map<Subject, ul > in_subjectsAndRequirements);

	std::string getName() const;

	void setTeacherForSubject(Subject in_subject, Teacher *in_pTeacher);
	void setSubjectAndRequirement(Subject in_subject, hourObjectiveAndFill in_objectiveAndFill);

	bool addOneHour(Slot* in_slot, Subject in_subject);
	bool removeOneHour(Slot* in_slot, Subject in_subject);

	std::map <Subject, Teacher*> getTeachers() const;
	std::map<Subject, hourObjectiveAndFill > getSubjectAndRequirements() const;
	
	std::vector<Subject> notFilledObjective();
private:

	std::string _name;
	std::map<Subject, hourObjectiveAndFill > _subjectsAndRequirements;
	std::map <Subject, Teacher*> _dedicatedTeacher;
};

bool operator==(const Class &in_lValue, const Class &in_rValue);
bool operator<=(const Class &in_lValue, const Class &in_rValue);
bool operator>=(const Class &in_lValue, const Class &in_rValue);
bool operator<(const Class &in_lValue, const Class &in_rValue);
bool operator>(const Class &in_lValue, const Class &in_rValue);
#endif // CLASS_H
