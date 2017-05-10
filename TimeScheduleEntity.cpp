#include "stdafx.h"
#include "TimeScheduleEntity.h"



TimeScheduleEntity::TimeScheduleEntity()
{
}

TimeScheduleEntity::TimeScheduleEntity(std::vector<Schedule::session> in_allSessions)
{
	Schedule::session sTest(tm(), 3);
	Schedule::SessionPrototype<Slot> spTest(sTest);

	for (Schedule::session tmpSession : in_allSessions)
	{
		_allSlotsPerSessions[tmpSession] = Schedule::SessionPrototype<Slot>(tmpSession);
	}
}


TimeScheduleEntity::~TimeScheduleEntity()
{
}

void TimeScheduleEntity::addSlot(Slot * in_slot)
{
	Schedule::session sessionTmp = in_slot->ts.session;
	_allSlotsPerSessions[sessionTmp].at(in_slot->ts, in_slot);
}

void TimeScheduleEntity::freeSlot(Slot * in_slot)
{
	Schedule::session tmpSession = in_slot->ts.session;
	// Should be in a upper level function
	//in_slot->occupied = false;
	_allSlotsPerSessions[tmpSession].at(in_slot->ts, nullptr);
}

double TimeScheduleEntity::score()
{
	double dScore = 0;
	std::function<double(ul)> fSum = [](ul in_ul) { 
		double _sum = 0.0;
		for (ul ulCpt = 0; ulCpt < in_ul; ulCpt++)
		{
			_sum += ulCpt;
		}
		return _sum; 
	};
	for (auto pSessionAndSlots : _allSlotsPerSessions)
	{
		auto sessionContent = pSessionAndSlots.second.getContent();
		bool activated = false;
		ul start, end;
		ul ulRunningIndex = 0;
		for (auto pTimeSlotAndSlot : sessionContent)
		{
			// start is the first used slot
			if (pTimeSlotAndSlot.second != nullptr && activated == false)
			{
				activated = true;
				start = ulRunningIndex;
				end = ulRunningIndex;
			}
			if (activated && pTimeSlotAndSlot.second != nullptr)
			{
				end = ulRunningIndex;
			}
			ulRunningIndex++;
		}
		if (activated)
		{
			dScore += fSum(sessionContent.size() - (end - start));
		}
	}
	return dScore;
}

std::map<Schedule::session, Schedule::SessionPrototype<Slot>> TimeScheduleEntity::getAllSlotsPerSession() const
{
	return _allSlotsPerSessions;
}
