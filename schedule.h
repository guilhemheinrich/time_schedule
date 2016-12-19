#ifndef SCHEDULE_H
#define SCHEDULE_H


enum class Day {MONDAY = 0, TUESDAY = 1, WEDNESDAY = 2, THURSDAY = 3, FRIDAY = 4, SUNDAY = 5};
class Schedule
{
public:
    Schedule(){}
    Schedule(Day day, unsigned long hour, unsigned long minute);
    static const unsigned long session_last = 1;

    int encode() const;
    static Schedule decode(int footprint);
private:
    Day _day = Day::MONDAY;
    unsigned long _hour;
    unsigned long _minute;

};

#endif // SCHEDULE_H
