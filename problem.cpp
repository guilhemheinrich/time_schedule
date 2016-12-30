#include "problem.h"

Problem::Problem()
{


}

std::set<Schedule> Problem::sAllSchedules() const
{
	return _sAllSchedules;
}

void Problem::setSAllSchedules(const std::set<Schedule>& sAllSchedules)
{
	_sAllSchedules = sAllSchedules;
}



std::set<Teacher> Problem::sTeachers() const
{
    return _sTeachers;
}

void Problem::setSTeachers(const std::set<Teacher> &sTeachers)
{
    _sTeachers = sTeachers;
}

std::set<Class> Problem::sClasses() const
{
    return _sClasses;
}

void Problem::setSClasses(const std::set<Class> &sClasses)
{
    _sClasses = sClasses;
}

std::set<Room> Problem::sAllRooms() const
{
	return _sAllRooms;
}

void Problem::setSAllRooms(const std::set<Room>& sAllRooms)
{
	_sAllRooms = sAllRooms;
}

