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

	std::map<Schedule::session, Schedule::SessionPrototype<Slot*> > getAllSlotsPerSession() const;
	std::map<Schedule::session, Schedule::SessionPrototype<double> > getAllNeighborhoodStructurePerSessions() const;

	std::set<Schedule::session> getAllSessions() const;

protected:
	std::set<Schedule::session> _allSessions;
	std::map<Schedule::session, Schedule::SessionPrototype<Slot*> >  _allSlotsPerSessions;
	std::map<Schedule::session, Schedule::SessionPrototype<double> >  _allNeighborhoodStructurePerSessions;
};

