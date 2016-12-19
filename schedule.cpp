#include "schedule.h"

Schedule::Schedule(Day day, unsigned long hour, unsigned long minute):
_day(day)
{
    if (hour < 24 && minute <61)
    {
        _hour = hour;
        _minute = minute;
    }
}

int Schedule::encode() const
{
    int out_footprint = 0;
    out_footprint += (int) _day * 24 * 60;
    out_footprint += (int) _hour * 60;
    out_footprint += (int) _minute;
    return out_footprint;
}

Schedule Schedule::decode(int footprint)
{
    Schedule out_schedule;
    unsigned long ulTmp = footprint % (24 * 60);
    unsigned long minute = footprint % 60;
//    unsigned long hour = footprint;
//    Day day = (Day) ;


}
