#include "room.h"

Room::Room()
{

}

Room::Room(std::set<int> in_availibility)
{
    _availability = in_availibility;
}

bool Room::occupyBy(int in_scheduleID, Teacher in_teacher, Class in_class)
{
    if (_availability.erase(in_scheduleID) > 0)
    {
        _occupied[in_scheduleID] = std::pair<Teacher, Class>(in_teacher, in_class);
        return true;
    }
    return false;
}

bool Room::free(int in_scheduleID)
{
    if (_occupied.erase(in_scheduleID) > 0)
    {
        _availability.insert(in_scheduleID);
        return true;
    }
    return false;
}
