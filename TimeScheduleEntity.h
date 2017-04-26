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


	// Return the score
	double score();


private:
	std::map<SessionID, Schedule::SessionPrototype<bool> >  _weekFilledSlots;
};

