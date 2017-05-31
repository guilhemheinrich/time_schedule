#ifndef SOLUTION_H
#define SOLUTION_H
#include <vector>
#include "IncludedHeaders.h"
#include "class.h"
#include "room.h"
#include "schedule.h"
#include "teacher.h"


class Solution
{
public:
	Solution();
	Solution(std::vector<Class> in_allClasses, std::vector<Teacher> in_allTeachers, std::vector<Slot> in_allSlots, std::set<Schedule::time_slot> *in_pAllTimeSlots);
	~Solution();

	void generate();
	void mutate(double in_genomePercent = 0.1);

	double getScore() const;
private:
	double score = 0.0;
	std::vector<Class> _allClasses;
	std::vector<Teacher> _allTeachers;
	std::set<Schedule::time_slot> *_pAllTimeSlots;
	std::vector<Slot*> _allSlots;
	std::vector<Slot*> _allUnusedSlots;

	// Internals
	std::map<Schedule::time_slot, std::vector<Slot*> > _mapTS;
	//std::vector<std::pair<Class*, std::set<Schedule::time_slot> >> _timeSlotPerClasses;
	std::map<Class*, std::set<Schedule::time_slot> > _timeSlotPerClasses;
	std::set<Schedule::time_slot> _globallyUsedTimeSlots;
};


#endif // SOLUTION_H
