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

	void addSlot(Slot* in_slot);
	void freeSlot(Slot* in_slot);
	// Return the score
	double score();

	std::map<Schedule::session, Schedule::SessionPrototype<Slot> > getAllSlotsPerSession() const;


protected:
	std::map<Schedule::session, Schedule::SessionPrototype<Slot> >  _allSlotsPerSessions;
};

