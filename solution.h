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
	Solution(std::vector<Class> in_allClasses, std::vector<Teacher> in_allTeachers, std::vector<Slot*> _in_allSlots);
	~Solution();
private:
	std::vector<Class> _allClasses;
	std::vector<Teacher> _allTeachers;
	std::vector<Slot*> _allSlots;
	std::vector<Slot*> _allUnusedSlots;


};


#endif // SOLUTION_H
