#include <QCoreApplication>
#include "schedule.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::set<int> base_schedule = Schedule::buildRegularCalendar();
    for (auto iID : base_schedule)
    {
        Schedule tmpSchedule = Schedule::decode(iID);
        cout << "Base ID" << iID << "correspond to " << to_string(tmpSchedule.getDay()) << " " << tmpSchedule.getHour() << " " << tmpSchedule.getMinute() << endl;
        tmpSchedule = Schedule::decode(tmpSchedule.next());
        if (base_schedule.count(tmpSchedule.encode()) != 0)
        {
            cout << "is nexto to" << endl;
            cout << "Base ID" << iID << "correspond to " << to_string(tmpSchedule.getDay()) << " " << tmpSchedule.getHour() << " " << tmpSchedule.getMinute() << endl;
        }
        else
        {
            cout << "doesn't have an upper neighbor" << endl;
        }

    }
    cin.get();
    return 0;

    return a.exec();
}
