#ifndef TEACHER_H
#define TEACHER_H

#include <string>
#include "IncludedHeaders.h"
class Teacher
{
public:
	Teacher();
	Teacher(std::string in_name);
private:
	ul _ID;
	std::string _name;
	ul _nbHourToGive = 15;
	ul _hourGiven = 0;
};

#endif // TEACHER_H