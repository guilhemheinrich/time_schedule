#ifndef TEACHER_H
#define TEACHER_H

#include <string>
#include "IncludedHeaders.h"
struct Teacher
{
public:
	Teacher();
	Teacher(std::string in_name);

	std::string _name;
	ul _nbHourToGive = 15;
	ul _hourGiven = 0;
	Subject _subject;
};

#endif // TEACHER_H