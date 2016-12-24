#ifndef SLOT_H
#define SLOT_H
#include "room.h"
#include "schedule.h"


// Slot is the product of a room and a shedule
class Slot
{
public:
    Slot(Schedule in_schedule, Room in_room);
    Schedule _schedule;
    Room _room;

    int encode();
    int decode();
private:
    Slot();

};

#endif // SLOT_H
