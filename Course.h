#ifndef COURSE_H
#define COURSE_H

#include <string>

class Course {
private:
    std::string courseNumber;
    std::string courseName;
    std::string schedule;
    double price;

public:
    // Constructors
    Course();
    Course(std::string cNum, std::string cName, std::string sched, double p);

    // Getters and Setters
    std::string getCourseNumber() const;
    std::string getCourseName() const;
    std::string getSchedule() const;
    double getPrice() const;

    void setCourseNumber(const std::string& cNum);
    void setCourseName(const std::string& cName);
    void setSchedule(const std::string& sched);
    void setPrice(double p);
};

#endif