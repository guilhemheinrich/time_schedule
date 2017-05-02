// time_schedule.cpp : définit le point d'entrée pour l'application console.
//

//#include "stdafx.h"
#include "schedule.h"
#include "room.h"
#include "Calendar.h"
#include "class.h"
#include "teacher.h"
#include "mapper.h"

#include <iostream>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
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
	root_day.tm_mon = 0;   // month of year from 0 to 11
	root_day.tm_year = 1;  // year since 1900
	root_day.tm_wday = 1;  // days since sunday
	root_day.tm_yday = 1;  // days since January 1st
	root_day.tm_isdst = 1; // hours of daylight savings time

	Schedule::initalizeRootDay(root_day);
	// representation of a week as a time schedule
	std::vector<Schedule::session> sessions_template;
	
	// Let's build 6 days, starting from the root day, from 8 am to 4pm (8 hours long)

	for (ul ulCpt = 0; ulCpt < 6; ulCpt++)
	{
		tm tmStartDay = root_day;
		tmStartDay.tm_yday += ulCpt;
		tmStartDay.tm_mday += ulCpt;
		tmStartDay.tm_wday += ulCpt;
		sessions_template.push_back(Schedule::session(tmStartDay, 8));
	}


	std::set<Schedule::time_slot> allTimeSlot = Schedule::buildAllTimeSlots(sessions_template);
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

	Teacher tMath(sessions_template, "tMath", Subject::MATH);
	Teacher tFrench(sessions_template, "tFrench", Subject::FRENCH);
	Teacher tHistory(sessions_template, "tHistory", Subject::HISTORY);
	Teacher tSport(sessions_template, "tSport", Subject::SPORT);
	Teacher tEnglish(sessions_template, "tEnglish", Subject::ENGLISH);
	//Teacher *ptEnglish = new Teacher(sessions_template, "tEnglish", Subject::ENGLISH);

	// Class schedule

	// Création des classes
	std::map<Subject, ul > standardClass;
	standardClass[Subject::MATH] = 4;
	standardClass[Subject::FRENCH] = 4;
	standardClass[Subject::HISTORY] = 4;
	standardClass[Subject::SPORT] = 4;
	standardClass[Subject::ENGLISH] = 4;
	Class c1(sessions_template, "c1", standardClass);
	Class c2(sessions_template, "c2", standardClass);
	Class c3(sessions_template, "c3", standardClass);

	std::vector<Class> allClasses;
	allClasses.push_back(c1);
	allClasses.push_back(c2);
	allClasses.push_back(c3);

	// Association des professeurs
	for (auto &pClass : allClasses)
	{
		pClass.setTeacherForSubject(Subject::MATH, &tMath);
		pClass.setTeacherForSubject(Subject::FRENCH, &tFrench);
		pClass.setTeacherForSubject(Subject::HISTORY, &tHistory);
		pClass.setTeacherForSubject(Subject::SPORT, &tSport);
		pClass.setTeacherForSubject(Subject::ENGLISH, &tEnglish);
		//pClass.setTeacherForSubject(Subject::ENGLISH, ptEnglish);

	}

	// Première génération



	// Build the cpt of remaining hours by class (same order as allClasses)
	std::vector<std::pair<Class*, ul> > cptByClasses;

	ul ulCpt = 0;
	for (auto &pClass : allClasses)
	{
		cptByClasses.push_back(std::pair<Class*, ul>(&pClass, 0));
		std::map<Subject, hourObjectiveAndFill > mRemainingHours = pClass.getSubjectAndRequirements();
		for (auto pSubjectANdHourObjectiveAndFill : mRemainingHours)
		{
			cptByClasses[ulCpt].second += pSubjectANdHourObjectiveAndFill.second.objective;
		}
		ulCpt++;
	}

	// Keep track of the time slots used per classes
	std::vector<std::pair<Class*, std::set<Schedule::time_slot> >> timeSlotPerClasses;
	timeSlotPerClasses.resize(allClasses.size());
	std::set<Schedule::time_slot> globallyUsedTimeSlots;

	// Keep track of the  time_slots a class uses

	
	// Set the mapping function, 
	std::map<Schedule::time_slot, std::vector<Slot*> > mapTS = mapper::reducer<Schedule::time_slot>(allSlots);

	// random slot(class, room, time_slot) made in two steps : first we choose the class , then the (room, time_slot), among available ones
	// P(class, room, time_slot) = P(class)  x P(time_slot, room | class) = P(class)  x P(time_slot, room), independency

	srand (time(NULL));
	while (cptByClasses.size() != 0)
	{
		// Choose a random class
		cout << "there is " << cptByClasses.size() << " classes remaining" << endl;
		ul ulRandomClass = rand() % cptByClasses.size();
		Class* pCurrentClass = cptByClasses[ulRandomClass].first;

		cout << "picked class : " << pCurrentClass->getName() << " which is class number " << ulRandomClass << endl;

		// Pick an availble time slot
		std::vector<Schedule::time_slot> tmpAvailableSlots;
		std::vector<Schedule::time_slot> availableTimeSlots;
		set_difference(allTimeSlot.begin(), allTimeSlot.end(), timeSlotPerClasses[ulRandomClass].second.begin(), timeSlotPerClasses[ulRandomClass].second.end(), std::inserter(tmpAvailableSlots, tmpAvailableSlots.begin()));
		set_difference(tmpAvailableSlots.begin(), tmpAvailableSlots.end(), globallyUsedTimeSlots.begin(), globallyUsedTimeSlots.end(), std::inserter(availableTimeSlots, availableTimeSlots.begin()));

		cout << "there is " << availableTimeSlots.size() << " time slots remaining" << endl;

		ul ulPickedTimeSlot = rand() % availableTimeSlots.size();

		cout << "picked time_slot " << ulPickedTimeSlot << endl;

		// Pick an available slot
		std::vector<Slot*> availableSlots = mapTS[availableTimeSlots[ulPickedTimeSlot]];
		if (mapTS[availableTimeSlots[ulPickedTimeSlot]].size() == 0)
		{
			cout << "this is not an available time slot" << endl;
		}
		cout << "there is " << mapTS[availableTimeSlots[ulPickedTimeSlot]].size() << " slots remaining" << endl;

		ul ulPickedSlot = rand() % availableSlots.size();

		cout << "picked slot " << ulPickedTimeSlot << endl;


		// Pick an available subject
		std::vector<Subject> availableSubjects = pCurrentClass->notFilledObjective();
		if (availableSubjects.size() == 0)
		{
			cout << "this class doesnt possess any subject to fill anymore" << endl;
			cptByClasses.erase(cptByClasses.begin() + ulRandomClass);
			continue;
		}
		ul ulPickedSubject = rand() % availableSubjects.size();

		// Do the stuff accordingly
		// Class & teacher
		
		if (pCurrentClass->addOneHour(availableSlots[ulPickedSlot], availableSubjects[ulPickedSubject]))
		{			
			//cout << "hour added" << endl;
		}

		// Remove the slot from the available ones and add the time slot to the used for the class
		mapTS[availableTimeSlots[ulPickedTimeSlot]].erase(mapTS[availableTimeSlots[ulPickedTimeSlot]].begin() + ulPickedSlot);
		if (mapTS[availableTimeSlots[ulPickedTimeSlot]].size() == 0)
		{
			mapTS.erase(availableTimeSlots[ulPickedTimeSlot]);
			globallyUsedTimeSlots.insert(availableTimeSlots[ulPickedTimeSlot]);
		}

		timeSlotPerClasses[ulRandomClass].first = pCurrentClass;
		timeSlotPerClasses[ulRandomClass].second.insert(availableTimeSlots[ulPickedTimeSlot]);

		cout << "________________________" << endl;
	}


	cin.get();
    return 0;
}

