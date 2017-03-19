// time_schedule.cpp : définit le point d'entrée pour l'application console.
//

//#include "stdafx.h"
#include "schedule.h"
#include "room.h"
#include "Calendar.h"
#include "class.h"
#include "teacher.h"
#include <iostream>
#include <ctime>
using namespace std;

//void testBuildingRegularCalendar()
//{
//	std::set<int> base_schedule = Schedule::buildRegularCalendar();
//	for (auto iID : base_schedule)
//	{
//		Schedule tmpSchedule = Schedule::decode(iID);
//		cout << "Base ID" << iID << "correspond to " << to_string(tmpSchedule.getDay()) << " " << tmpSchedule.getHour() << " " << tmpSchedule.getMinute() << endl;
//		tmpSchedule = Schedule::decode(tmpSchedule.next());
//		if (base_schedule.count(tmpSchedule.encode()) != 0)
//		{
//			cout << "is nexto to " << endl;
//			cout << "Base ID" << iID << " correspond to " << to_string(tmpSchedule.getDay()) << " " << tmpSchedule.getHour() << " " << tmpSchedule.getMinute() << endl;
//		}
//		else
//		{
//			cout << "doesn't have an upper neighbor" << endl;
//		}
//		cout << endl;
//	}
//	cin.get();
//}


struct test_struct {
	std::string string;
	int i;
};

int main()
{
	// Building the time structure
	tm root_day;
	root_day.tm_sec = 1;   // seconds of minutes from 0 to 61
	root_day.tm_min = 0;   // minutes of hour from 0 to 59
	root_day.tm_hour = 0;  // hours of day from 0 to 24
	root_day.tm_mday = 1;  // day of month from 1 to 31
	root_day.tm_mon = 1;   // month of year from 0 to 11
	root_day.tm_year = 1;  // year since 1900
	root_day.tm_wday = 2;  // days since sunday
	root_day.tm_yday = 1;  // days since January 1st
	root_day.tm_isdst = 1; // hours of daylight savings time

	Schedule::initalizeRootDay(root_day);

	std::vector<Schedule::time_slot> allTimeSlot = Schedule::buildAllTimeSlots();
	Room room1(std::string("r1"));
	Room room2(std::string("r2"));
	std::vector<Room> allRoom;
	allRoom.push_back(room1);
	allRoom.push_back(room2);
	cout << "allRoom.size() : " << allRoom.size() << endl;
	cout << "Schedule::allTimeSlot.size() : " << allTimeSlot.size() << endl;

	Calendar calendar(allTimeSlot, allRoom);
	calendar.buildAllSlots();

	std::vector<Slot*> allSlots = calendar.getAllSlots();
	char buffer[80];
	cout << "allSlots.size() : " << allSlots.size() << endl;
	for (auto slot : allSlots)
	{
		const tm* tmpTm = &(slot->ts.start);

		strftime(buffer, sizeof(buffer), "%d-%m-%Y %I:%M:%S", tmpTm);
		std::string str(buffer);
		cout << "Room : " << slot->room._name << endl;
		cout << "ts start : " << str << endl;
		tmpTm = &(slot->ts.end);
		strftime(buffer, sizeof(buffer), "%d-%m-%Y %I:%M:%S", tmpTm);
		str = buffer;
		cout << "ts end : " << str << endl;
	}

	// Creating the classes and teachers

	Teacher * tMath = new Teacher("tMath");
	Teacher * tFrench= new Teacher("tFrench");
	Teacher * tHistory= new Teacher("tHistory");
	Teacher * tSport= new Teacher("tSport");
	Teacher * tEnglish = new Teacher("tEnglish");

	// Class schedule

	std::map<Subject, ul > standardClass;
	standardClass[Subject::MATH] = 4;
	standardClass[Subject::FRENCH] = 4;
	standardClass[Subject::HISTORY] = 4;
	standardClass[Subject::SPORT] = 4;
	standardClass[Subject::ENGLISH] = 4;
	Class *c1 = new Class("c1", standardClass);
	Class *c2 = new Class("c2", standardClass);
	Class *c3 = new Class("c3", standardClass);

	std::vector<Class*> allClasses;
	allClasses.push_back(c1);
	allClasses.push_back(c2);
	allClasses.push_back(c3);

	for (auto pClass : allClasses)
	{
		pClass->setTeacherForSubject(Subject::MATH, tMath);
		pClass->setTeacherForSubject(Subject::FRENCH, tFrench);
		pClass->setTeacherForSubject(Subject::HISTORY, tHistory);
		pClass->setTeacherForSubject(Subject::SPORT, tSport);
		pClass->setTeacherForSubject(Subject::ENGLISH, tEnglish);
	}

	cin.get();
    return 0;
}

