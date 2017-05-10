#include "solution.h"
#include "mapper.h"

#include <algorithm>
#include <map>
// For debugging
#include <iostream>

Solution::Solution()
{

}

Solution::Solution(std::vector<Class> in_allClasses, std::vector<Teacher> in_allTeachers, std::vector<Slot> in_allSlots, std::set<Schedule::time_slot> *in_pAllTimeSlots):
	_allClasses(in_allClasses), _allTeachers(in_allTeachers), _pAllTimeSlots(in_pAllTimeSlots)
{
	for (Slot tmpSlot : in_allSlots)
	{
		Slot *pSlot = new Slot(tmpSlot);
		_allSlots.push_back(pSlot);
	}
	//for (Class tmpClass : in_allClasses)
	//{
	//	_allClasses.push_back(tmpClass);
	//}

	//for (Teacher tmpTeacher : in_allTeachers)
	//{
	//	_allTeachers.push_back(tmpTeacher);
	//}

	// We need to initialize the correct pointers to teachers from the classes.
	// For that, we will create new pointers to point to the teachers and classes
	std::map< std::string, Class*> classNameToPointer;
	std::map<std::string, Teacher*> teacherNamePointer;


	for (auto &refClass : _allClasses)
	{
		classNameToPointer[refClass.getName()] = &refClass;
	}
	for (auto &refTeacher : _allTeachers)
	{
		teacherNamePointer[toString(refTeacher.getSubject()) + "_" + refTeacher.getName()] = &refTeacher;
	}

	for (auto &refClass : _allClasses)
	{
		std::map <Subject, Teacher*> tmpTeacherForClassBySubject = refClass.getTeachers();
		for (auto pSubjectAndPteacher : tmpTeacherForClassBySubject)
		{
			// Find the relevent teacher
			std::string subject_teacher = toString(pSubjectAndPteacher.first) + "_" + pSubjectAndPteacher.second->getName();
			Teacher *pTeacher = teacherNamePointer[subject_teacher];
			refClass.setTeacherForSubject(pSubjectAndPteacher.first, pTeacher);
		}
	}

	for (auto &refTeacher : _allTeachers)
	{
		std::set <Class*> tmpClasses = refTeacher.getClasses();
		for (auto pClass : tmpClasses)
		{
			// Find the relevent teacher
			std::string className = pClass->getName();
			Class *pClass = classNameToPointer[className];
			refTeacher.addClass(pClass);
		}
	}
}

Solution::~Solution()
{
}

void Solution::generate()
{
	// Build the cpt of remaining hours by class (same order as allClasses)
	//std::vector<std::pair<Class*, ul> > cptByClasses;

	ul ulCpt = 0;
	for (auto &pClass : _allClasses)
	{
		_cptByClasses.push_back(std::pair<Class*, ul>(&pClass, 0));
		std::map<Subject, hourObjectiveAndFill > mRemainingHours = pClass.getSubjectAndRequirements();
		for (auto pSubjectANdHourObjectiveAndFill : mRemainingHours)
		{
			_cptByClasses[ulCpt].second += pSubjectANdHourObjectiveAndFill.second.objective;
		}
		ulCpt++;
	}

	// Keep track of the time slots used per classes
	//std::vector<std::pair<Class*, std::set<Schedule::time_slot> >> timeSlotPerClasses;
	_timeSlotPerClasses.resize(_allClasses.size());
	std::set<Schedule::time_slot> globallyUsedTimeSlots;

	// Keep track of the  time_slots a class uses


	// Set the mapping function, 
	std::map<Schedule::time_slot, std::vector<Slot*> > mapTS = mapper::reducer<Schedule::time_slot>(_allSlots);

	// random slot(class, room, time_slot) made in two steps : first we choose the class , then the (room, time_slot), among available ones
	// P(class, room, time_slot) = P(class)  x P(time_slot, room | class) = P(class)  x P(time_slot, room), independency


	while (_cptByClasses.size() != 0)
	{
		// Choose a random class
		//std::cout << "there is " << cptByClasses.size() << " classes remaining" << std::endl;
		ul ulRandomClass = rand() % _cptByClasses.size();
		Class* pCurrentClass = _cptByClasses[ulRandomClass].first;

		//std::cout << "picked class : " << pCurrentClass->getName() << " which is class number " << ulRandomClass << std::endl;

		// Pick an availble time slot
		std::vector<Schedule::time_slot> tmpAvailableSlots;
		std::vector<Schedule::time_slot> availableTimeSlots;
		set_difference((*_pAllTimeSlots).begin(), (*_pAllTimeSlots).end(), _timeSlotPerClasses[ulRandomClass].second.begin(), _timeSlotPerClasses[ulRandomClass].second.end(), std::inserter(tmpAvailableSlots, tmpAvailableSlots.begin()));
		set_difference(tmpAvailableSlots.begin(), tmpAvailableSlots.end(), globallyUsedTimeSlots.begin(), globallyUsedTimeSlots.end(), std::inserter(availableTimeSlots, availableTimeSlots.begin()));

		//std::cout << "there is " << availableTimeSlots.size() << " time slots remaining" << std::endl;

		ul ulPickedTimeSlot = rand() % availableTimeSlots.size();

		//std::cout << "picked time_slot " << ulPickedTimeSlot << std::endl;

		// Pick an available slot
		std::vector<Slot*> availableSlots = mapTS[availableTimeSlots[ulPickedTimeSlot]];
		if (mapTS[availableTimeSlots[ulPickedTimeSlot]].size() == 0)
		{
			//std::cout << "this is not an available time slot" << std::endl;
		}
		//std::cout << "there is " << mapTS[availableTimeSlots[ulPickedTimeSlot]].size() << " slots remaining" << std::endl;

		ul ulPickedSlot = rand() % availableSlots.size();

		//std::cout << "picked slot " << ulPickedTimeSlot << std::endl;


		// Pick an available subject
		std::vector<Subject> availableSubjects = pCurrentClass->notFilledObjective();
		if (availableSubjects.size() == 0)
		{
			//std::cout << "this class doesnt possess any subject to fill anymore" << std::endl;
			_cptByClasses.erase(_cptByClasses.begin() + ulRandomClass);
			continue;
		}
		ul ulPickedSubject = rand() % availableSubjects.size();

		// Do the stuff accordingly
		// Class & teacher

		if (pCurrentClass->addOneHour(availableSlots[ulPickedSlot], availableSubjects[ulPickedSubject]))
		{
			////std::cout << "hour added" << std::endl;
		}

		// Remove the slot from the available ones and add the time slot to the used for the class
		mapTS[availableTimeSlots[ulPickedTimeSlot]].erase(mapTS[availableTimeSlots[ulPickedTimeSlot]].begin() + ulPickedSlot);
		if (mapTS[availableTimeSlots[ulPickedTimeSlot]].size() == 0)
		{
			mapTS.erase(availableTimeSlots[ulPickedTimeSlot]);
			globallyUsedTimeSlots.insert(availableTimeSlots[ulPickedTimeSlot]);
		}

		_timeSlotPerClasses[ulRandomClass].first = pCurrentClass;
		_timeSlotPerClasses[ulRandomClass].second.insert(availableTimeSlots[ulPickedTimeSlot]);

		// Fill the slot
		availableSlots[ulPickedSlot]->occupied = true;
		availableSlots[ulPickedSlot]->pClass = pCurrentClass;
		availableSlots[ulPickedSlot]->pTeacher = pCurrentClass->getTeachers()[availableSubjects[ulPickedSubject]];

		//std::cout << "________________________" << std::endl;
	}

	//for (auto &tmpClass : allClasses)
	//{
	//	std::cout << tmpClass.score() << std::endl;
	//}

	//for (auto tmpTeacher : allTeacher)
	//{
	//	std::cout << tmpTeacher->score() << std::endl;
	//}
}

void Solution::mutate()
{
	// Philosophy here is to mutate according to the slots themselves.
	// First step is then to record for each used slot the number of "global neighbors",
	// which can be up to 4 if the slot is "well rounded" :
	// 2 for both the class part and the teacher one


}

double Solution::getScore() const
{
	double totalScore = 0.0;
	for (Class refClass : _allClasses)
	{
		// DEBUG
		std::cout << refClass.score() << std::endl;
		totalScore += refClass.score();
	}
	for (Teacher refTeacher : _allTeachers)
	{
		std::cout << refTeacher.score() << std::endl;
		totalScore += refTeacher.score();
	}
	return totalScore;
}

