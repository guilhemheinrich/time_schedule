#ifndef SLOT_H
#define SLOT_H
#include "room.h"
#include "schedule.h"


// Slot is the product of a room and a shedule
class Slot
{
public:
    Slot(Schedule in_schedule, Room in_room);

    int encode();
    static Slot decode();

	bool occupyBy(int in_scheduleID, Teacher in_teacher, Class in_class);
	bool free(int in_scheduleID);
private:
    Schedule _schedule;
    Room _room;
	// ID of schedules
	std::set<int> _availability;
	std::map<int, std::pair<Teacher, Class> > _occupied;

    Slot();

};

#endif // SLOT_H
