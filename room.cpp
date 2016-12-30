#include "room.h"

int Room::_cpt = 0;

Room::Room(std::string in_name)
{
	_ID = _cpt;
	_name = in_name;
	_cpt++;
}

Room::Room(std::string in_name, std::set<int> in_availibility)
{
	_ID = _cpt;
	_name = in_name;
	_cpt++;
}
