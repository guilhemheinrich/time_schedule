#include "room.h"

ul Room::_cpt = 0;
std::vector<std::reference_wrapper<Room> > Room::_allRoom;

Room::Room(std::string in_name)
{
	_name = in_name;
	_ID = _cpt;
	_allRoom.push_back(*this);
	_cpt++;

}

Room::Room(ul in_ID)
{
	//_ID = in_ID;
	//_name = getName(in_ID);
	(*this) = _allRoom[in_ID];
}

ul Room::getID() const
{
	return _ID;
}

std::string Room::getName()
{
	return _name;
}

std::string Room::getName(ul in_ID)
{
	std::string out_name;
	if (in_ID < _allRoom.size())
	{
		out_name = _allRoom[in_ID].get().getName();
	}
	return out_name;
}

bool Room::operator==(Room in_rValue)
{
	return _name == in_rValue._name;
}

bool Room::operator<=(Room in_rValue)
{
	return _name <= in_rValue._name;
}

bool Room::operator>=(Room in_rValue)
{
	return _name >= in_rValue._name;
}

bool Room::operator<(Room in_rValue)
{
	return !(*this >= in_rValue);
}

bool Room::operator>(Room in_rValue)
{
	return !(*this <= in_rValue);
}