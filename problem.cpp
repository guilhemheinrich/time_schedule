#include "problem.h"

Problem::Problem()
{


}

std::set<int> Problem::sAllSchedulesID() const
{
    return _sAllSchedulesID;
}

void Problem::setSAllSchedulesID(const std::set<int> &sAllSchedulesID)
{
    _sAllSchedulesID = sAllSchedulesID;
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

std::set<int> Problem::sAllRoomsID() const
{
    return _sAllRoomsID;
}

void Problem::setSAllRoomsID(const std::set<int> &sAllRoomsID)
{
    _sAllRoomsID = sAllRoomsID;
}
