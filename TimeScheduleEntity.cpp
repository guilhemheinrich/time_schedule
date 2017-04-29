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
		auto sessionSlots = pSessionAndSlots.second;
		bool activated = false;
		ul start, end;
		ul ulRunningIndex = 0;
		//for (auto pTimeSlotAndSlot : sessionSlots)
		//{

		//	// start is the first used slot
		//	if (pTimeSlotAndSlot.second != nullptr && activated == false)
		//	{
		//		activated = true;
		//		start = ulRunningIndex;
		//		end = ulRunningIndex;
		//	}
		//	if (activated && pTimeSlotAndSlot.second != nullptr)
		//	{
		//		end = ulRunningIndex;
		//	}
		//}
		//dScore += fSum(sessionSlots.size() - (end - start));
	}
	return dScore;
}
