#ifndef PROBLEM_H
#define PROBLEM_H

#include <set>
#include <vector>
#include <algorithm>
#include "IncludedHeaders.h"
#include "teacher.h"
#include "class.h"
#include "schedule.h"
#include "room.h"
class Problem
{
public:
    Problem();

    std::vector<Schedule> vSchedules() const;
    void setVSchedules(std::vector<Schedule> vSchedules);

    std::vector<Teacher> vTeachers() const;
    void setVTeachers(const std::vector<Teacher> &vTeachers);

    std::vector<Class> vClasses() const;
    void setVClasses(const std::vector<Class> &vClasses);

    std::vector<Room> vRooms() const;
    void setVRooms(const std::vector<Room> &vRooms);


private:
    std::vector<Schedule> _vSchedules;
    std::vector<Room> _vRooms;
    std::vector<Teacher> _vTeachers;
    std::vector<Class> _vClasses;

};


#endif // PROBLEM_H
