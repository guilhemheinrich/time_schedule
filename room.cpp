#include "room.h"

Room::Room(std::string in_name):
	_name(in_name)
{
}

bool operator==(const Room &in_lValue, const Room &in_rValue)
{
	return in_lValue._name == in_rValue._name;
}

bool operator<=(const Room &in_lValue, const Room &in_rValue)
{
	return in_lValue._name <= in_rValue._name;
}

bool operator>=(const Room &in_lValue, const Room &in_rValue)
{
	return in_lValue._name >= in_rValue._name;
}

bool operator<(const Room &in_lValue, const Room &in_rValue)
{
	return !(in_lValue >= in_rValue);
}

bool operator>(const Room &in_lValue, const Room &in_rValue)
{
	return !(in_lValue <= in_rValue);
}