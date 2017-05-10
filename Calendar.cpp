#include "stdafx.h"
#include "Calendar.h"


Calendar::Calendar()
{
}

Calendar::Calendar(std::set<Schedule::time_slot> in_allTimeSlots, std::vector<Room> in_allRooms):
	_allTimeSlots(in_allTimeSlots), _allRooms(in_allRooms)
{
}


Calendar::~Calendar()
{
}

int Calendar::buildAllSlots()
{
	int cpt = 0;
	for (auto ts : _allTimeSlots)
	{
		for (auto room : _allRooms)
		{
			Slot tmpSlot(room, ts);
			_allSlots.push_back(tmpSlot);
			_slotsByRoom[room].push_back(tmpSlot);
			_slotsBySchedule[ts].push_back(tmpSlot);
			cpt++;
		}

	}
	return cpt;
}

const std::vector<Slot> Calendar::getAllSlots() const
{
	return _allSlots;
}

Slot::Slot(Room in_room, Schedule::time_slot in_ts):
room(in_room), ts(in_ts)
{
}

double Slot::score() const
{
	double score = 0.0;
	if (pTeacher == nullptr || pClass == nullptr)
	{
		return 0.0;
	}
	//pTeacher->
	return score;
}
