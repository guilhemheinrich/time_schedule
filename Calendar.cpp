#include "stdafx.h"
#include "Calendar.h"


Calendar::Calendar()
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
			_slotsByRoom[room].push_back(_allSlots[cpt]);
			_slotsBySchedule[ts].push_back(_allSlots[cpt]);
			cpt++;
		}

	}
	return cpt;
}

Slot::Slot(Room & in_room, Schedule::time_slot in_ts):
room(in_room), ts(in_ts)
{
}
