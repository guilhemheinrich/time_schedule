#pragma once
#include <map>

#include "schedule.h"
#include "Calendar.h"

namespace mapper
{

	// mapper
	template<typename TYPE>
	std::pair<TYPE, Slot*> mapper(Slot* in_slot);
	// reducer
	template<typename TYPE>
	std::map<TYPE, std::vector<Slot*> > reducer(std::vector<Slot*> in_allSlot);



}