#pragma once

#include <vector>
#include <map>
#include <functional>

#include "room.h"
#include "schedule.h"
struct Slot
{
	Room &room;
	Schedule::time_slot &ts;

	Slot *next = nullptr;
};

class Calendar
{
public:
	Calendar();
	Calendar(std::vector<Slot>);
	~Calendar();



private:
	std::map<Room, std::vector<std::reference_wrapper<Slot> >> _slotsByRoom;
	std::map<Schedule::time_slot, std::vector<std::reference_wrapper<Slot> >> _slotsBySchedule;
	std::vector<Slot> _allSlots;
};

