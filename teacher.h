#ifndef TEACHER_H
#define TEACHER_H

#include <string>
class Teacher
{
public:
	Teacher();
	Teacher(std::string in_name);
private:
	std::string _name;
};

#endif // TEACHER_H