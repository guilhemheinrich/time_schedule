#pragma once

#include <functional>
#include <vector>
#include <map>
#include <ctime>

#include "schedule.h"

class TimeScheduleEntity
{
public:
	TimeScheduleEntity();
	~TimeScheduleEntity();

	void setMapping(std::function<ul(tm)> in_mapping);

	// Return the score
	double score();

	// Return the mapping
	ul mapping(tm in_timeStamp);

private:
	std::map<SessionID, Schedule::SessionPrototype<bool> >  _weekFilledSlots;
	std::function<ul(tm)> _mapping;
};

