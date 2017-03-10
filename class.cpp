#include "class.h"

//ul Class::_cpt = 0;
//std::vector<std::reference_wrapper<Class> > Class::_allClass;

Class::Class(std::string in_name, std::map<Subject, ul > in_subjectsAndRequirements) :
	_name(in_name)
{
		for (auto subjectAndReq : in_subjectsAndRequirements)
		{
			_subjectsAndRequirements[subjectAndReq.first].objective = subjectAndReq.second;
			_dedicatedTeacher[subjectAndReq.first] = nullptr;
		}
}

void Class::setTeacherForSubject(Subject in_subject, Teacher * in_pTeacher)
{
	_dedicatedTeacher.at(in_subject) = in_pTeacher;
}

//Class::Class(ul in_ID)
//{
//	(*this) = _allClass[in_ID];
//}
