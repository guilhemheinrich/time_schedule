#ifndef PROBLEM_H
#define PROBLEM_H

#include <set>
#include <vector>
#include "teacher.h"
#include "class.h"
class Problem
{
public:
    Problem();

    std::set<int> sAllSchedulesID() const;
    void setSAllSchedulesID(const std::set<int> &sAllSchedulesID);

    std::set<Teacher> sTeachers() const;
    void setSTeachers(const std::set<Teacher> &sTeachers);

    std::set<Class> sClasses() const;
    void setSClasses(const std::set<Class> &sClasses);

    std::set<int> sAllRoomsID() const;
    void setSAllRoomsID(const std::set<int> &sAllRoomsID);

private:
    // Calendar
    std::set<int> _sAllSchedulesID;
    // Rooms
    std::set<int> _sAllRoomsID;

    std::set<Teacher> _sTeachers;
    std::set<Class> _sClasses;
//    std::set<>
};

#endif // PROBLEM_H
