#ifndef CLASS_H
#define CLASS_H
#include <string>
#include <vector>
#include <map>
#include <functional>
#include "IncludedHeaders.h"
struct hourObjectiveAndFill
{
	ul objective;
	ul fill = 0;
};

class Class
{
public:
	Class(std::string in_name, std::map<Subject, hourObjectiveAndFill > in_subjectsAndRequirements);
	Class(ul in_ID);
private:
	//static ul _cpt;
	static std::vector<std::reference_wrapper<Class>> _allClass;
	std::string _name;
	std::map<Subject, hourObjectiveAndFill > _subjectsAndRequirements;
};

#endif // CLASS_H
