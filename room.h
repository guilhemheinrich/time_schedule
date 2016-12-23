#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <set>
#include <map>
#include "schedule.h"
#include "teacher.h"
#include "class.h"
class Room
{
public:
	Room();
	Room(std::set<int> in_availibility);

	bool occupyBy();
private:
    int _ID;

	// ID of schedules
    std::set<int> _availability;
    std::map<int, std::pair<Teacher, Class> > _occupied;
};

#endif // ROOM_H
