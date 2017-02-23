#ifndef SLOT_H
#define SLOT_H

#include <string.h>
#include "IncludedHeaders.h"
#include "room.h"
#include "schedule.h"


// Slot is the product of a room and a shedule
namespace Slot
{
    //Slot(Schedule in_schedule, Room in_room);

	int encode(std::pair<Schedule, Room> in_pScheduleAndRoom, std::string &out_sSlot);
	int decode(std::string in_sSlot, std::pair<Schedule, Room> &out_pScheduleAndRoom);

	std::string next(std::string in_sSlot);


	//bool occupyBy(int in_scheduleID, Teacher in_teacher, Class in_class);
	//bool free(int in_scheduleID);

 //   Schedule _schedule;
 //   Room _room;
	//// ID of schedules
	//std::set<int> _availability;
	//std::map<int, std::pair<Teacher, Class> > _occupied;

 //   Slot();

};

#endif // SLOT_H
