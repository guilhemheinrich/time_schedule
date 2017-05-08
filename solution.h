#ifndef SOLUTION_H
#define SOLUTION_H
#include <vector>
#include "IncludedHeaders.h"
#include "class.h"
#include "room.h"
#include "schedule.h"
//#include "slot.h"
#include "teacher.h"


class Solution
{
public:
	Solution();
	Solution(std::vector<Class> in_allClasses, std::vector<Teacher> in_allTeachers, std::vector<Slot*> _in_allSlots, std::set<Schedule::time_slot> *in_pAllTimeSlots);
	~Solution();

	void generate();

	double getScore() const;
private:
	double score = 0.0;
	std::vector<Class> _allClasses;
	std::vector<Teacher> _allTeachers;
	std::set<Schedule::time_slot> *_pAllTimeSlots;
	std::vector<Slot*> _allSlots;
	std::vector<Slot*> _allUnusedSlots;


};


#endif // SOLUTION_H
