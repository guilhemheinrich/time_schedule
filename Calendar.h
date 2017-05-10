#pragma once

#include <vector>
#include <set>
#include <map>
#include <functional>

#include "IncludedHeaders.h"
#include "room.h"
#include "schedule.h"

class Teacher;
class Class;

struct Slot
{
	Slot(Room in_room, Schedule::time_slot in_ts);
	Room room;
	Schedule::time_slot ts;

	bool occupied = false;
	Teacher *pTeacher = nullptr;
	Class *pClass = nullptr;

	double score() const;

//private:
//	Slot *previous = nullptr;
//	Slot *next = nullptr;
};

class Calendar
{
public:
	Calendar();
	Calendar(std::set<Schedule::time_slot> in_allTimeSlots, std::vector<Room> in_allRooms);
	~Calendar();

	int buildAllSlots();

	const std::vector<Slot> getAllSlots() const;


private:
	std::set<Schedule::time_slot> _allTimeSlots;
	std::vector<Room> _allRooms;

	std::map<Room, std::vector<Slot>> _slotsByRoom;
	std::map<Schedule::time_slot, std::vector<Slot>> _slotsBySchedule;
	std::vector<Slot> _allSlots;
};

