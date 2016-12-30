#include "slot.h"



Slot::Slot(Schedule in_schedule, Room in_room):_schedule(in_schedule),
    _room(in_room)
{

}

Slot::Slot()
{

}


bool Slot::occupyBy(int in_scheduleID, Teacher in_teacher, Class in_class)
{
	if (_availability.erase(in_scheduleID) > 0)
	{
		_occupied[in_scheduleID] = std::pair<Teacher, Class>(in_teacher, in_class);
		return true;
	}
	return false;
}

bool Slot::free(int in_scheduleID)
{
	if (_occupied.erase(in_scheduleID) > 0)
	{
		_availability.insert(in_scheduleID);
		return true;
	}
	return false;
}