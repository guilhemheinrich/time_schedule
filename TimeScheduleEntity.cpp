#include "stdafx.h"
#include "TimeScheduleEntity.h"
#include <functional>


TimeScheduleEntity::TimeScheduleEntity()
{
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
	for (auto sessionBool : _weekFilledSlots)
	{
		bool activated = false;
		ul start, end;
		for (ul ulIndex = 0; ulIndex < sessionBool.second.size(); ulIndex++)
		{
			// start is the first used slot
			if (*sessionBool.second[ulIndex].second == true && activated == false)
			{
				activated = true;
				start = ulIndex;
				end = ulIndex;
			}
			if (activated && *sessionBool.second[ulIndex].second == true)
			{
				end = ulIndex;
			}
		}
		dScore += fSum(sessionBool.second.size() - (end - start));

	}
	return dScore;
}
