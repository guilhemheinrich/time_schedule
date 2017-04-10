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

class Class : TimeScheduleEntity
{
public:
	Class(std::string in_name, std::map<Subject, ul > in_subjectsAndRequirements);
	//Class(ul in_ID);

	void setTeacherForSubject(Subject in_subjct, Teacher* in_pTeacher);
	void setSubjectAndRequirement(Subject in_subjct, hourObjectiveAndFill in_objectiveAndFill);

	std::map <Subject, Teacher*> getTeachers() const;
	std::map<Subject, hourObjectiveAndFill > getSubjectAndRequirements() const;
private:

	std::string _name;
	std::map<Subject, hourObjectiveAndFill > _subjectsAndRequirements;
	std::map <Subject, Teacher*> _dedicatedTeacher;
};

#endif // CLASS_H
