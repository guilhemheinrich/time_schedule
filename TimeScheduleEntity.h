#pragma once

#include <functional>
#include <vector>
#include <map>
#include <ctime>

#include "schedule.h"
#include "Calendar.h"

class TimeScheduleEntity
{
public:
	TimeScheduleEntity();
	TimeScheduleEntity(std::vector<Schedule::session> in_allSessions);
	~TimeScheduleEntity();

	void add(Slot* in_slot);
	// Return the score
	virtual double score();




protected:
	std::map<Schedule::session, Schedule::SessionPrototype<Slot> >  _allSlotsPerSessions;
};

