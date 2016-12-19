#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <set>
#include "schedule.h"
class Room
{
public:
    Room();
private:
    char* _ID;
    std::set<int> _availability;
    std::set<int> _occupied;
};

#endif // ROOM_H
