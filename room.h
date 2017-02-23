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
class Room
{
public:
	Room(std::string in_name);
	Room(ul in_ID);


	ul getID() const;
	std::string getName();
	static std::string getName(ul in_ID);

	// For using shedule as Key
	bool operator==(Room in_rValue);
	bool operator<=(Room in_rValue);
	bool operator>=(Room in_rValue);
	bool operator<(Room in_rValue);
	bool operator>(Room in_rValue);

private:
	ul _ID;
	static ul _cpt;
	static std::vector<std::reference_wrapper<Room>> _allRoom;
	std::string _name;
};

#endif // ROOM_H
