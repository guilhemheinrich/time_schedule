#include "stdafx.h"
#include "mapper.h"


namespace mapper
{
	template<>
	std::pair<Schedule::time_slot, Slot*> mapper(Slot* in_slot)
	{
		std::pair<Schedule::time_slot, Slot*> out_result;
		out_result.first = in_slot->ts;
		out_result.second = in_slot;
		return out_result;
	}

	template<>
	std::map<Schedule::time_slot, std::vector<Slot*> > reducer(std::vector<Slot*> in_allSlot)
	{
		std::map<Schedule::time_slot, std::vector<Slot*> > out_map;
		for (auto pSlot : in_allSlot)
		{
			std::pair<Schedule::time_slot, Slot*> tmpPair = mapper<Schedule::time_slot>(pSlot);
			out_map[tmpPair.first].push_back(tmpPair.second);
		}
		return out_map;
	}

}