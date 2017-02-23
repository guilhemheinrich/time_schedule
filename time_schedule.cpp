// time_schedule.cpp : définit le point d'entrée pour l'application console.
//

//#include "stdafx.h"
#include "schedule.h"
#include "problem.h"
#include <iostream>
using namespace std;

void testBuildingRegularCalendar()
{
	std::set<int> base_schedule = Schedule::buildRegularCalendar();
	for (auto iID : base_schedule)
	{
		Schedule tmpSchedule = Schedule::decode(iID);
		cout << "Base ID" << iID << "correspond to " << to_string(tmpSchedule.getDay()) << " " << tmpSchedule.getHour() << " " << tmpSchedule.getMinute() << endl;
		tmpSchedule = Schedule::decode(tmpSchedule.next());
		if (base_schedule.count(tmpSchedule.encode()) != 0)
		{
			cout << "is nexto to " << endl;
			cout << "Base ID" << iID << " correspond to " << to_string(tmpSchedule.getDay()) << " " << tmpSchedule.getHour() << " " << tmpSchedule.getMinute() << endl;
		}
		else
		{
			cout << "doesn't have an upper neighbor" << endl;
		}
		cout << endl;
	}
	cin.get();
}

void testBuildProblem() 
{
	Problem problem;

};

int main()
{
	testBuildingRegularCalendar();
    return 0;
}

