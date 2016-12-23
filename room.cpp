#include "room.h"

Room::Room()
{

}

Room::Room(std::set<int> in_availibility)
{
	_availability = in_availibility;
}
