#include "stdafx.h"
#include "TimeScheduleEntity.h"



TimeScheduleEntity::TimeScheduleEntity()
{
}

TimeScheduleEntity::TimeScheduleEntity(std::vector<Schedule::session> in_allSessions)
{
	for (Schedule::session tmpSession : in_allSessions)
	{
		_allSessions.insert(tmpSession);
		_allSlotsPerSessions[tmpSession] = Schedule::SessionPrototype<Slot*>(tmpSession, nullptr);
		_allNeighborhoodStructurePerSessions[tmpSession] = Schedule::SessionPrototype<double>(tmpSession, 0.0);
	}

	// Set the slot score value to 1 for start and end
	for (auto &tmpSessionPrototypeNeighborSturcture : _allNeighborhoodStructurePerSessions)
	{
		auto tmpNeighborSturcture = tmpSessionPrototypeNeighborSturcture.second.getPointerContent();
		auto iteStart = tmpNeighborSturcture->begin();
		(*iteStart).second = 1.0;
		auto iteEnd = tmpNeighborSturcture->end();
		iteEnd--;
		(*iteEnd).second = 1.0;
	}
}


TimeScheduleEntity::~TimeScheduleEntity()
{
}

void TimeScheduleEntity::addSlot(Slot * in_slot)
{
	Schedule::session sessionTmp = in_slot->ts.session;
	_allSlotsPerSessions[sessionTmp].at(in_slot->ts, in_slot);
	Schedule::time_slot tmpTs = in_slot->ts;
	tmpTs++;
	if (_allNeighborhoodStructurePerSessions[sessionTmp].getContent().count(tmpTs) == 1)
	{
		_allNeighborhoodStructurePerSessions[sessionTmp][tmpTs] += 1.0;
	}
	else
	{
		_allNeighborhoodStructurePerSessions[sessionTmp][tmpTs--] += 1.0;
	}
	tmpTs = in_slot->ts;
	tmpTs--;
	if (_allNeighborhoodStructurePerSessions[sessionTmp].getContent().count(tmpTs) == 1)
	{
		_allNeighborhoodStructurePerSessions[sessionTmp][tmpTs] += 1.0;
	}
	else
	{
		_allNeighborhoodStructurePerSessions[sessionTmp][tmpTs++] += 1.0;
	}


}

void TimeScheduleEntity::freeSlot(Slot * in_slot)
{
	Schedule::session sessionTmp = in_slot->ts.session;
	_allSlotsPerSessions[sessionTmp].at(in_slot->ts, nullptr);
	Schedule::time_slot tmpTs = in_slot->ts;
	tmpTs++;
	if (_allNeighborhoodStructurePerSessions[sessionTmp].getContent().count(tmpTs) == 1)
	{
		_allNeighborhoodStructurePerSessions[sessionTmp][tmpTs] -= 1.0;
	}
	else
	{
		_allNeighborhoodStructurePerSessions[sessionTmp][tmpTs--] -= 1.0;
	}
	tmpTs = in_slot->ts;
	tmpTs--;
	if (_allNeighborhoodStructurePerSessions[sessionTmp].getContent().count(tmpTs) == 1)
	{
		_allNeighborhoodStructurePerSessions[sessionTmp][tmpTs] -= 1.0;
	}
	else
	{
		_allNeighborhoodStructurePerSessions[sessionTmp][tmpTs++] -= 1.0;
	}
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

std::map<Schedule::session, Schedule::SessionPrototype<Slot*>> TimeScheduleEntity::getAllSlotsPerSession() const
{
	return _allSlotsPerSessions;
}

std::map<Schedule::session, Schedule::SessionPrototype<double>> TimeScheduleEntity::getAllNeighborhoodStructurePerSessions() const
{
	return _allNeighborhoodStructurePerSessions;
}

std::set<Schedule::session> TimeScheduleEntity::getAllSessions() const
{
	return _allSessions;
}
