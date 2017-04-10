#ifndef TEACHER_H
#define TEACHER_H

#include <string>
#include <vector>
#include "IncludedHeaders.h"

class Teacher
{
public:
	Teacher(std::string in_name);
	Teacher(std::string in_name, Subject in_subject);

private:

	std::string _name;
	ul _nbHourToGive = 15;
	ul _hourGiven = 0;
	Subject _subject;

};

#endif // TEACHER_H