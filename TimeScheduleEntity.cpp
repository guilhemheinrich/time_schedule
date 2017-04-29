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

void TimeScheduleEntity::add(Slot * in_slot)
{
	Schedule::session sessionTmp = in_slot->ts.session;
	_allSlotsPerSessions[sessionTmp].at(in_slot->ts, in_slot);
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
		}
		dScore += fSum(sessionContent.size() - (end - start));
	}
	return dScore;
}
