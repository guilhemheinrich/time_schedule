#include "solution.h"

Solution::Solution()
{

}

Solution::Solution(std::vector<Class> in_allClasses, std::vector<Teacher> in_allTeachers, std::vector<Slot*> _in_allSlots):
	_allClasses(in_allClasses), _allTeachers(in_allTeachers), _allSlots(_in_allSlots)
{
}

Solution::~Solution()
{
}
