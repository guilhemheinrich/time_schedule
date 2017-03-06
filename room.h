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



	std::string _name;
};

// For using Room as Key

bool operator==(const Room &in_lValue, const Room &in_rValue);
bool operator<=(const Room &in_lValue, const Room &in_rValue);
bool operator>=(const Room &in_lValue, const Room &in_rValue);
bool operator<(const Room &in_lValue, const Room &in_rValue);
bool operator>(const Room &in_lValue, const Room &in_rValue);
#endif // ROOM_H
