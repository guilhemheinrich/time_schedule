#include "room.h"

Room::Room(std::string in_name):
	_name(in_name)
{
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