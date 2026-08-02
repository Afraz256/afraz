#include "Course.h"

Course::Course() : courseNumber(""), courseName(""), schedule(""), price(0.0) {}

Course::Course(std::string cNum, std::string cName, std::string sched, double p)
    : courseNumber(cNum), courseName(cName), schedule(sched), price(p) {}

std::string Course::getCourseNumber() const { return courseNumber; }
std::string Course::getCourseName() const { return courseName; }
std::string Course::getSchedule() const { return schedule; }
double Course::getPrice() const { return price; }

void Course::setCourseNumber(const std::string& cNum) { courseNumber = cNum; }
void Course::setCourseName(const std::string& cName) { courseName = cName; }
void Course::setSchedule(const std::string& sched) { schedule = sched; }
void Course::setPrice(double p) { price = p; }
