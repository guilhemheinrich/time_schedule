#include "solution.h"
#include "mapper.h"

#include <algorithm>
#include <map>
// For debugging
#include <iostream>

Solution::Solution()
{

}

Solution::Solution(const Solution & in_solution):
	_allClasses(in_solution._allClasses), _allTeachers(in_solution._allTeachers), _pAllTimeSlots(in_solution._pAllTimeSlots),
	_globallyUsedTimeSlots(in_solution._globallyUsedTimeSlots)
{
	// Shallow copy are made in the initilizator list
	// Now we handle deep copy of the containers

	// We need to initialize the correct pointers to teachers from the classes.
	// For that, we will create new pointers to point to the teachers and classes
	std::map<std::string, Class*> classNameToPointer;
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

	
	for (Slot *tmpSlot : in_solution._allSlots)
	{
		Slot *pSlot = new Slot(*tmpSlot);
		// HANDLE when there is a teacher and a class
		if (tmpSlot->pTeacher != nullptr)
		{
			// Bind the new slot with correct pointer
			// Parse teacher pointer to correct teacher
			std::string teacherName = toString(tmpSlot->pTeacher->getSubject());
			teacherName += "_" + tmpSlot->pTeacher->getName();
			Teacher *pTeacher = teacherNamePointer[teacherName];
			pSlot->pTeacher = pTeacher;
		}

		if (tmpSlot->pClass != nullptr)
		{
			// Parse class pointer to correct class
			std::string className = tmpSlot->pClass->getName();
			Class *pClass = classNameToPointer[className];
			pSlot->pClass = pClass;
		}
		_allSlots.push_back(pSlot);

	}

	//for (Slot *tmpSlot : in_solution._allUnusedSlots)
	//{
	//	Slot *pSlot = new Slot(*tmpSlot);
	//	_allUnusedSlots.push_back(pSlot);
	//}

	// Set the mapping ts internals, 
	
	for (Slot* pSlot : _allSlots)
	{
		if ( pSlot->pClass == nullptr)
		{
			_mapTS[pSlot->ts].push_back(pSlot);
		}
	}

	



	for (auto pClassAndSetTS : in_solution._timeSlotPerClasses)
	{
		std::string className = pClassAndSetTS.first->getName();
		Class * pClass = classNameToPointer[className];
		_timeSlotPerClasses[pClass] = pClassAndSetTS.second;

	}


}

Solution::Solution(std::vector<Class> in_allClasses, std::vector<Teacher> in_allTeachers, std::vector<Slot> in_allSlots, std::set<Schedule::time_slot> *in_pAllTimeSlots):
	_allClasses(in_allClasses), _allTeachers(in_allTeachers), _pAllTimeSlots(in_pAllTimeSlots)
{ 
	for (Slot tmpSlot : in_allSlots)
	{
		Slot *pSlot = new Slot(tmpSlot);
		_allSlots.push_back(pSlot);
	}

	// We need to initialize the correct pointers to teachers from the classes.
	// For that, we will create new pointers to point to the teachers and classes
	std::map<std::string, Class*> classNameToPointer;
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
	for (auto *pSlot : _allSlots)
	{
		delete pSlot;
	}

	//for (auto *pSlot : _allUnusedSlots)
	//{
	//	delete pSlot;
	//}
}

void Solution::generate()
{
	// Build the cpt of remaining hours by class (same order as allClasses)
	std::vector<std::pair<Class*, ul> > cptByClasses;

	ul ulCpt = 0;
	for (auto &pClass : _allClasses)
	{
		cptByClasses.push_back(std::pair<Class*, ul>(&pClass, 0));
		std::map<Subject, hourObjectiveAndFill > mRemainingHours = pClass.getSubjectAndRequirements();
		for (auto pSubjectANdHourObjectiveAndFill : mRemainingHours)
		{
			cptByClasses[ulCpt].second += pSubjectANdHourObjectiveAndFill.second.objective;
		}
		ulCpt++;
	}

	// Keep track of the time slots used per classes
	//std::vector<std::pair<Class*, std::set<Schedule::time_slot> >> timeSlotPerClasses;
	//_timeSlotPerClasses.resize(_allClasses.size());

	//std::set<Schedule::time_slot> globallyUsedTimeSlots;

	// Keep track of the  time_slots a class uses


	// Set the mapping function, 
	_mapTS = mapper::reducer<Schedule::time_slot>(_allSlots);

	// random slot(class, room, time_slot) made in two steps : first we choose the class , then the (room, time_slot), among available ones
	// P(class, room, time_slot) = P(class)  x P(time_slot, room | class) = P(class)  x P(time_slot, room), independency


	while (cptByClasses.size() != 0)
	{
		// Choose a random class
		//std::cout << "there is " << cptByClasses.size() << " classes remaining" << std::endl;
		ul ulRandomClass = rand() % cptByClasses.size();
		Class* pCurrentClass = cptByClasses[ulRandomClass].first;

		//std::cout << "picked class : " << pCurrentClass->getName() << " which is class number " << ulRandomClass << std::endl;

		// Pick an available time slot
		std::vector<Schedule::time_slot> tmpAvailableSlots;
		std::vector<Schedule::time_slot> availableTimeSlots;
		//set_difference((*_pAllTimeSlots).begin(), (*_pAllTimeSlots).end(), _timeSlotPerClasses[ulRandomClass].second.begin(), _timeSlotPerClasses[ulRandomClass].second.end(), std::inserter(tmpAvailableSlots, tmpAvailableSlots.begin()));
		set_difference((*_pAllTimeSlots).begin(), (*_pAllTimeSlots).end(), _timeSlotPerClasses[pCurrentClass].begin(), _timeSlotPerClasses[pCurrentClass].end(), std::inserter(tmpAvailableSlots, tmpAvailableSlots.begin()));
		set_difference(tmpAvailableSlots.begin(), tmpAvailableSlots.end(), _globallyUsedTimeSlots.begin(), _globallyUsedTimeSlots.end(), std::inserter(availableTimeSlots, availableTimeSlots.begin()));

		//std::cout << "there is " << availableTimeSlots.size() << " time slots remaining" << std::endl;

		ul ulPickedTimeSlot = rand() % availableTimeSlots.size();

		//std::cout << "picked time_slot " << ulPickedTimeSlot << std::endl;

		// Pick an available slot
		std::vector<Slot*> availableSlots = _mapTS[availableTimeSlots[ulPickedTimeSlot]];

		//std::cout << "there is " << mapTS[availableTimeSlots[ulPickedTimeSlot]].size() << " slots remaining" << std::endl;

		ul ulPickedSlot = rand() % availableSlots.size();

		//std::cout << "picked slot " << ulPickedTimeSlot << std::endl;


		// Pick an available subject
		std::vector<Subject> availableSubjects = pCurrentClass->notFilledObjective();
		if (availableSubjects.size() == 0)
		{
			//std::cout << "this class doesnt possess any subject to fill anymore" << std::endl;
			cptByClasses.erase(cptByClasses.begin() + ulRandomClass);
			continue;
		}
		ul ulPickedSubject = rand() % availableSubjects.size();

		// Do the stuff accordingly
		// Class & teacher

		if (pCurrentClass->addOneHour(availableSlots[ulPickedSlot], availableSubjects[ulPickedSubject]))
		{
			////std::cout << "hour added" << std::endl;
		}

		// Remove the slot from the available ones and add the time slot to the used ones for the class
		_mapTS[availableTimeSlots[ulPickedTimeSlot]].erase(_mapTS[availableTimeSlots[ulPickedTimeSlot]].begin() + ulPickedSlot);

		// If the map no longer give availables slots
		if (_mapTS[availableTimeSlots[ulPickedTimeSlot]].size() == 0)
		{
			_mapTS.erase(availableTimeSlots[ulPickedTimeSlot]);
			_globallyUsedTimeSlots.insert(availableTimeSlots[ulPickedTimeSlot]);
		}

		_timeSlotPerClasses[pCurrentClass].insert(availableTimeSlots[ulPickedTimeSlot]);

		// Fill the slot
		availableSlots[ulPickedSlot]->occupied = true;
		availableSlots[ulPickedSlot]->pClass = pCurrentClass;
		availableSlots[ulPickedSlot]->pTeacher = pCurrentClass->getTeachers()[availableSubjects[ulPickedSubject]];

		//std::cout << "________________________" << std::endl;
	}

}

void Solution::mutate(double in_genomePercent)
{
	// Philosophy here is to mutate according to the slots themselves.
	// First step is then to record for each used slot the number of "global neighbors",
	// which can be up to 4 if the slot is "well rounded" :
	// 2 for both the class part and the teacher one

	std::vector<Slot*> allSelectedSlots;
	std::vector<Slot*> allPickedSlots;
	std::vector<Slot*> allNullptTeacherSlots;
	std::vector<Slot*> allUnusedSlots;

	std::vector<Slot*> allSlotEntries;
	ul ulNumberOfSlots = 0;
	for (auto teacher : _allTeachers)
	{
		for (auto session : teacher.getAllSessions())
		{
			auto mapSessionsNeighborhoodStructure = teacher.getAllNeighborhoodStructurePerSessions()[session];
			auto mapSessionsSlot = teacher.getAllSlotsPerSession()[session];
			for (auto timeSlot : session)
			{
				if (mapSessionsSlot[timeSlot] == nullptr)
				{
					continue;
				}
				ulNumberOfSlots++;
				// Allow the exploration of all solution, the weight of a given slot vary between 1 ("good" slot) and 5 ("bad" slot)
				int slotScore = 5.0 - mapSessionsNeighborhoodStructure[timeSlot];
				//std::cout << "slotScore " << slotScore << std::endl;
				for (int cpt = 0; cpt < slotScore; cpt++)
				{
					allSlotEntries.push_back(mapSessionsSlot[timeSlot]);
				}
			}
		}
	}
	
	ul ulNumberOfMutation = (ul)(in_genomePercent * ulNumberOfSlots) % ulNumberOfSlots;

	for (ul ulCpt = 0; ulCpt < ulNumberOfMutation; ulCpt++)
	{
		// Select 1 slot at random
		ul ulRandomSlot = rand() % allSlotEntries.size();
		Slot *pPickedSlot = allSlotEntries[ulRandomSlot];
		Teacher *pPickedTeacher = pPickedSlot->pTeacher;
		Class *pPickedClass = pPickedSlot->pClass;

		/* Debug */
		allSelectedSlots.push_back(pPickedSlot);

		// remove it

		allSlotEntries.erase(std::remove(allSlotEntries.begin(), allSlotEntries.end(), pPickedSlot), allSlotEntries.end());
		pPickedSlot->pTeacher = nullptr;
		pPickedSlot->pClass = nullptr;
		pPickedSlot->occupied = false;
		pPickedTeacher->removeOneHour(pPickedSlot);
		pPickedClass->removeOneHour(pPickedSlot, pPickedTeacher->getSubject());
		//_allUnusedSlots.push_back(pPickedSlot);
		//allUnusedSlots.push_back(pPickedSlot);



		// Reinsert the slot in the available ones
		_timeSlotPerClasses[pPickedClass].erase(pPickedSlot->ts);
		_mapTS[pPickedSlot->ts].push_back(pPickedSlot);
		_globallyUsedTimeSlots.erase(pPickedSlot->ts);

		// TODO : Redraw one slot
		// Pick an available time slot
		std::vector<Schedule::time_slot> tmpAvailableSlots;
		std::vector<Schedule::time_slot> availableTimeSlots;
		set_difference((*_pAllTimeSlots).begin(), (*_pAllTimeSlots).end(), _timeSlotPerClasses[pPickedClass].begin(), _timeSlotPerClasses[pPickedClass].end(), std::inserter(tmpAvailableSlots, tmpAvailableSlots.begin()));
		set_difference(tmpAvailableSlots.begin(), tmpAvailableSlots.end(), _globallyUsedTimeSlots.begin(), _globallyUsedTimeSlots.end(), std::inserter(availableTimeSlots, availableTimeSlots.begin()));

		ul ulPickedTimeSlot = rand() % availableTimeSlots.size();
		std::vector<Slot*> availableSlots = _mapTS[availableTimeSlots[ulPickedTimeSlot]];

		ul ulPickedSlot = rand() % availableSlots.size();
		pPickedClass->addOneHour(availableSlots[ulPickedSlot], pPickedTeacher->getSubject());

		//Debug
		allPickedSlots.push_back(availableSlots[ulPickedSlot]);

		_mapTS[availableTimeSlots[ulPickedTimeSlot]].erase(_mapTS[availableTimeSlots[ulPickedTimeSlot]].begin() + ulPickedSlot);

		// If the map no longer give availables slots
		if (_mapTS[availableTimeSlots[ulPickedTimeSlot]].size() == 0)
		{
			_mapTS.erase(availableTimeSlots[ulPickedTimeSlot]);
			_globallyUsedTimeSlots.insert(availableTimeSlots[ulPickedTimeSlot]);
		}

		_timeSlotPerClasses[pPickedClass].insert(availableTimeSlots[ulPickedTimeSlot]);

		// Fill the slot
		availableSlots[ulPickedSlot]->occupied = true;
		availableSlots[ulPickedSlot]->pClass = pPickedClass;
		availableSlots[ulPickedSlot]->pTeacher = pPickedTeacher;



	}

	for (auto teacher : _allTeachers)
	{
		for (auto session : teacher.getAllSessions())
		{

			auto mapSessionsSlot = teacher.getAllSlotsPerSession()[session];
			for (auto timeSlot : session)
			{
				if (mapSessionsSlot[timeSlot] == nullptr)
				{
					continue;
				}
				if (mapSessionsSlot[timeSlot]->pTeacher == nullptr)
				{
					std::cout << "nullptr in " << mapSessionsSlot[timeSlot] << std::endl;
					//allNullptTeacherSlots.push_back(availableSlots[ulPickedSlot]);
				}
			}
		}
	}

}

double Solution::getScore() const
{
	double totalScore = 0.0;
	for (Class refClass : _allClasses)
	{
		totalScore += refClass.score();
	}
	for (Teacher refTeacher : _allTeachers)
	{
		totalScore += refTeacher.score();
	}
	return totalScore;
}

std::vector<Solution> breeding(std::vector<Solution> in_vSolutions, double in_dTopPercentage)
{

	return std::vector<Solution>();
}
