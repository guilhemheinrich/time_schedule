#include "class.h"

//ul Class::_cpt = 0;
std::vector<std::reference_wrapper<Class> > Class::_allClass;

Class::Class(std::string in_name, std::map<Subject, hourObjectiveAndFill > in_subjectsAndRequirements) :
	_name(in_name),
	_subjectsAndRequirements(in_subjectsAndRequirements)
{
	for (auto subAndReq : _subjectsAndRequirements)
	{
		slotXsubject _slotAndSubject;
		_slotAndSubject.subject = subAndReq.first;
		if (subAndReq.second.objective == 1)
		{
			_vOneHour.push_back(_slotAndSubject);
		}
		else if (subAndReq.second.objective == 2)
		{
			_vTwoHours.push_back(_slotAndSubject);
		}

	}
	_allClass.push_back(*this);
	//_cpt++;
}

Class::Class(ul in_ID)
{
	(*this) = _allClass[in_ID];
}
