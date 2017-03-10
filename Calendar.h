#pragma once

#include <vector>
#include <map>
#include <functional>

#include "room.h"
#include "schedule.h"
struct Slot
{
	Slot(Room in_room, Schedule::time_slot in_ts);
	Room room;
	Schedule::time_slot ts;

	Slot *next = nullptr;
};

class Calendar
{
public:
	Calendar();
	Calendar(std::vector<Schedule::time_slot> in_allTimeSlots, std::vector<Room> in_allRooms);
	~Calendar();

	int buildAllSlots();

	const std::vector<Slot*> getAllSlots() const;
	const std::vector<Slot*> getSlotsByRooms (Room in_room) const;
	const std::vector<Slot*> getSlotsBySchedule(Schedule::time_slot in_ts) const;

private:
	std::vector<Schedule::time_slot> _allTimeSlots;
	std::vector<Room> _allRooms;

	std::map<Room, std::vector<Slot*>> _slotsByRoom;
	std::map<Schedule::time_slot, std::vector<Slot*>> _slotsBySchedule;
	std::vector<Slot*> _allSlots;
};
