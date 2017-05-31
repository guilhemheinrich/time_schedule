// time_schedule.cpp : définit le point d'entrée pour l'application console.
//

//#include "stdafx.h"
#include "schedule.h"
#include "room.h"
#include "Calendar.h"
#include "class.h"
#include "teacher.h"
#include "mapper.h"
#include "solution.h"

#include <iostream>
#include <fstream>
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

int main(int argc, char** argv)
{
	if (argc != 4)
	{
		cout << "unappropriate parameter : " << endl;
		cout << "first argument is the number of solution" << endl;
		cout << "second argument is the number of generation" << endl;
		cout << "third argument is the mutation rate (0<m<1)" << endl;
	}
	// argv[1] is the number of solution
	// argv[2] is the number of generation
	// argv[3] is the mutation rate

	ofstream outputFile;
	outputFile.open("timeSchedule_log.txt");
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

	std::vector<Slot> allSlots = calendar.getAllSlots();
	//char buffer[80];
	//cout << "allSlots.size() : " << allSlots.size() << endl;
	//for (auto slot : allSlots)
	//{
	//	const tm* tmpTm = &(slot->ts.start);

	//	strftime(buffer, sizeof(buffer), "%d-%m-%Y %I:%M:%S", tmpTm);
	//	std::string str(buffer);
	//	cout << "Room : " << slot->room._name << endl;
	//	cout << "ts start : " << str << endl;
	//	tmpTm = &(slot->ts.end);
	//	strftime(buffer, sizeof(buffer), "%d-%m-%Y %I:%M:%S", tmpTm);
	//	str = buffer;
	//	cout << "ts end : " << str << endl;
	//}

	// Creating the classes and teachers

	Teacher tMath(sessions_template, "tMath", Subject::MATH);
	Teacher tFrench(sessions_template, "tFrench", Subject::FRENCH);
	Teacher tHistory(sessions_template, "tHistory", Subject::HISTORY);
	Teacher tSport(sessions_template, "tSport", Subject::SPORT);
	Teacher tEnglish(sessions_template, "tEnglish", Subject::ENGLISH);
	//Teacher *ptEnglish = new Teacher(sessions_template, "tEnglish", Subject::ENGLISH);
	std::vector<Teacher> allTeacher;
	allTeacher.push_back(tMath);
	allTeacher.push_back(tFrench);
	allTeacher.push_back(tHistory);
	allTeacher.push_back(tSport);
	allTeacher.push_back(tEnglish);


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
	}

	// Première génération
	srand(time(NULL));

	//Solution firstSolution(allClasses, allTeacher, allSlots, &allTimeSlot);
	//firstSolution.generate();


	//Solution secondSolution(allClasses, allTeacher, allSlots, &allTimeSlot);
	//secondSolution.generate();
	ul ulNbMutation;
	ul ulSolutionNumber;
	double dMutationPercent;

	sscanf_s(argv[1], "%d", &ulSolutionNumber);
	sscanf_s(argv[2], "%d", &ulNbMutation);
	sscanf_s(argv[3], "%lf", &dMutationPercent);

	std::vector<double> vStartScore;
	std::vector<std::vector<double> > vMutateScore;
	vMutateScore.resize(ulSolutionNumber);


	//startScore[0] = firstSolution.getScore();
	//startScore[1] = secondSolution.getScore();

	std::vector<Solution*> vAllSolution;
	for (ul ulCpt = 0; ulCpt < ulSolutionNumber; ulCpt++)
	{
		vAllSolution.push_back(new Solution(allClasses, allTeacher, allSlots, &allTimeSlot));
		vAllSolution[ulCpt]->generate();
		vStartScore.push_back(vAllSolution[ulCpt]->getScore());
	}

	for (ul ulGeneration = 0; ulGeneration < ulNbMutation; ulGeneration++)
	{
		for (ul ulCpt = 0; ulCpt < ulSolutionNumber; ulCpt++)
		{
			vAllSolution[ulCpt]->mutate(dMutationPercent);
			vMutateScore[ulCpt].push_back(vAllSolution[ulCpt]->getScore());
		}
		//firstSolution.mutate(dMutationPercent);
		//secondSolution.mutate(dMutationPercent);
		//mutateScore[ulCpt][0] = firstSolution.getScore();
		//mutateScore[ulCpt][1] = secondSolution.getScore();
	}

	for (ul ulCpt = 0; ulCpt < ulSolutionNumber; ulCpt++)
	{
		outputFile << "Solution " << ulCpt << " startScore " << vStartScore[ulCpt] << endl;
		for (ul ulGeneration = 0; ulGeneration < ulNbMutation; ulGeneration++)
		{
			outputFile << "mutation " << ulGeneration << " " << vMutateScore[ulCpt][ulGeneration] << endl;
		}
		outputFile << endl;
	}

	// csv generation
	cout << "csv outputing" << endl;
	ofstream csvFile;
	std::string csvName = "data_pop_" + to_string(ulSolutionNumber) + "_gen _" + to_string(ulNbMutation) + "_mrate_" + to_string(dMutationPercent) + ".csv";
	csvFile.open(csvName);
	for (ul ulCpt = 0; ulCpt < ulSolutionNumber; ulCpt++)
	{
		csvFile << vStartScore[ulCpt] << ";";
		for (ul ulGeneration = 0; ulGeneration < ulNbMutation; ulGeneration++)
		{
			csvFile << vMutateScore[ulCpt][ulGeneration] << ";";
		}
		csvFile << endl;
	}

	cin.get();
    return 0;
}

