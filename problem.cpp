#include "problem.h"

Problem::Problem()
{
}

std::vector<Schedule> Problem::vSchedules() const
{
	return _vSchedules;
}

void Problem::setVSchedules(std::vector<Schedule> vSchedules)
{
	_vSchedules = vSchedules;
	//_vSchedules.clear();
	//for (auto schedule : vSchedules)
	//{
	//	_vSchedules.push_back(schedule);
	//}
	////_vSchedules = vSchedules;
	//std::sort(_vSchedules.begin(), _vSchedules.end());
	//auto last = std::unique(_vSchedules.begin(), _vSchedules.end());
	//_vSchedules.erase(last, _vSchedules.end());
}
//
//std::vector<Teacher> Problem::vTeachers() const
//{
//	return _vTeachers;
//}
//
//void Problem::setVTeachers(const std::vector<Teacher>& vTeachers)
//{
//	_vTeachers.clear();
//	_vTeachers = vTeachers;
//	std::sort(_vTeachers.begin(), _vTeachers.end());
//	auto last = std::unique(_vTeachers.begin(), _vTeachers.end());
//	_vTeachers.erase(last, _vTeachers.end());
//}
//
//std::vector<Class> Problem::vClasses() const
//{
//	return _vClasses;
//}
//
//void Problem::setVClasses(const std::vector<Class>& vClasses)
//{
//	_vClasses.clear();
//	_vClasses = vClasses;
//	std::sort(_vClasses.begin(), _vClasses.end());
//	auto last = std::unique(_vClasses.begin(), _vClasses.end());
//	_vClasses.erase(last, _vClasses.end());
//}
//
//std::vector<Room> Problem::vRooms() const
//{
//	return _vRooms;
//}
//
//void Problem::setVRooms(const std::vector<Room>& vRooms)
//{
//	_vRooms.clear();
//	_vRooms = vRooms;
//	std::sort(_vRooms.begin(), _vRooms.end());
//	auto last = std::unique(_vRooms.begin(), _vRooms.end());
//	_vRooms.erase(last, _vRooms.end());
//}
