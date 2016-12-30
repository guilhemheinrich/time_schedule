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
	Room(std::string in_name);
	Room(std::string in_name, std::set<int> in_availibility);


private:
	static int _cpt;
    int _ID;
	std::string _name;


};

#endif // ROOM_H
