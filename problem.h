#ifndef PROBLEM_H
#define PROBLEM_H

#include <set>
#include <vector>
#include "teacher.h"
#include "class.h"
#include "schedule.h"
#include "room.h"
class Problem
{
public:
    Problem();

    std::set<Schedule> sAllSchedules() const;
    void setSAllSchedules(const std::set<Schedule> &sAllSchedules);

    std::set<Teacher> sTeachers() const;
    void setSTeachers(const std::set<Teacher> &sTeachers);

    std::set<Class> sClasses() const;
    void setSClasses(const std::set<Class> &sClasses);

    std::set<Room> sAllRooms() const;
    void setSAllRooms(const std::set<Room> &sAllRooms);

private:
    // Calendar
    std::set<Schedule> _sAllSchedules;
    // Rooms
    std::set<Room> _sAllRooms;

    std::set<Teacher> _sTeachers;
    std::set<Class> _sClasses;
//    std::set<>
};

#endif // PROBLEM_H
