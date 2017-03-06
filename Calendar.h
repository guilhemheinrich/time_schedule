#pragma once

#include <vector>
#include <map>
#include <functional>

#include "room.h"
#include "schedule.h"
struct Slot
{
	Slot(Room &in_room, Schedule::time_slot in_ts);
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

	int buildAllSlots();

private:
	std::vector<Schedule::time_slot> _allTimeSlots;
	std::vector<Room> _allRooms;

	std::map<Room, std::vector<std::reference_wrapper<Slot> >> _slotsByRoom;
	std::map<Schedule::time_slot, std::vector<std::reference_wrapper<Slot> >> _slotsBySchedule;
	std::vector<Slot> _allSlots;
};

