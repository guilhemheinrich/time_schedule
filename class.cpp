#include "class.h"

//ul Class::_cpt = 0;
//std::vector<std::reference_wrapper<Class> > Class::_allClass;

Class::Class(std::vector<Schedule::session> in_allSessions, std::string in_name, std::map<Subject, ul > in_subjectsAndRequirements) :
	TimeScheduleEntity(in_allSessions), _name(in_name)
{
		for (auto subjectAndReq : in_subjectsAndRequirements)
		{
			_subjectsAndRequirements[subjectAndReq.first].objective = subjectAndReq.second;
			_dedicatedTeacher[subjectAndReq.first] = nullptr;
		}
}

std::string Class::getName() const
{
	return _name;
}

void Class::setTeacherForSubject(Subject in_subject, Teacher * in_pTeacher)
{
	_dedicatedTeacher.at(in_subject) = in_pTeacher;
}

void Class::setSubjectAndRequirement(Subject in_subject, hourObjectiveAndFill in_objectiveAndFill)
{
	_subjectsAndRequirements[in_subject] = in_objectiveAndFill;
}

bool Class::addOneHour(Slot* in_slot, Subject in_subject)
{
	if (_dedicatedTeacher[in_subject]->addOneHour(in_slot) && _subjectsAndRequirements[in_subject].fill < _subjectsAndRequirements[in_subject].objective)
	{
		_subjectsAndRequirements[in_subject].fill++;
		add(in_slot);
		return true;
	}
	else
	{
		return false;
	}

}

std::map<Subject, Teacher*> Class::getTeachers() const
{
	return _dedicatedTeacher;
}

std::map<Subject, hourObjectiveAndFill> Class::getSubjectAndRequirements() const
{
	return _subjectsAndRequirements;
}

std::vector<Subject> Class::notFilledObjective()
{
	std::vector<Subject> out_vNotFilledObjective;
	for (auto pSubjectAndObjective : _subjectsAndRequirements) 
	{
		if (pSubjectAndObjective.second.fill != pSubjectAndObjective.second.objective)
		{
			out_vNotFilledObjective.push_back(pSubjectAndObjective.first);
		}
	}
	return out_vNotFilledObjective;
}

//Class::Class(ul in_ID)
//{
//	(*this) = _allClass[in_ID];
//}
