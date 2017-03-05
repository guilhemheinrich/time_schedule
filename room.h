#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <set>
#include <map>
#include <functional>
#include "IncludedHeaders.h"
#include "schedule.h"
#include "teacher.h"
#include "class.h"
struct Room
{
	Room(std::string in_name);

	// For using Room as Key
	bool operator==(Room in_rValue);
	bool operator<=(Room in_rValue);
	bool operator>=(Room in_rValue);
	bool operator<(Room in_rValue);
	bool operator>(Room in_rValue);

	std::string _name;
};

#endif // ROOM_H
