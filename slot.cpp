#include "slot.h"
#include "StringHelper.h"


//
//bool Slot::occupyBy(int in_scheduleID, Teacher in_teacher, Class in_class)
//{
//	if (_availability.erase(in_scheduleID) > 0)
//	{
//		_occupied[in_scheduleID] = std::pair<Teacher, Class>(in_teacher, in_class);
//		return true;
//	}
//	return false;
//}
//
//bool Slot::free(int in_scheduleID)
//{
//	if (_occupied.erase(in_scheduleID) > 0)
//	{
//		_availability.insert(in_scheduleID);
//		return true;
//	}
//	return false;
//}

namespace Slot {
	 int encode(std::pair<Schedule, Room> in_pScheduleAndRoom, std::string &out_sSlot)
	{
		out_sSlot = in_pScheduleAndRoom.first.encode() + "_" + in_pScheduleAndRoom.second.getID();
		return 1;
	}

	 int decode(std::string in_sSlot, std::pair<Schedule, Room> &out_pScheduleAndRoom)
	{
		std::vector<std::string> vSplittedContent = splitOver(in_sSlot, "_");

		if (vSplittedContent.size() != 2)
		{
			return 0;
		}
		out_pScheduleAndRoom.first = Schedule::decode(std::atol(vSplittedContent[0].c_str()));
		out_pScheduleAndRoom.second = Room(std::atol(vSplittedContent[1].c_str()));
		return 1;
	}
	 std::string next(std::string in_sSlot)
	 {
		 std::vector<std::string> vSplittedContent = splitOver(in_sSlot, "_");

		 if (vSplittedContent.size() != 2)
		 {
			return std::string();
		 }
		 std::string out_sSlot;
		 return out_sSlot;
	 }
}
