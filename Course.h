#ifndef COURSE_H
#define COURSE_H

#include <string>

/* One course: PRG210, "Programming Fundamentals", M/W, 499.99.
   Strings and a double only, nothing on the heap, so no destructor. */
class Course {
private:
    std::string courseNumber;
    std::string courseName;
    std::string schedule;
    double price;

public:
    // new Course[n] builds every slot before we fill any, so this is required.
    Course();
    Course(std::string cNum, std::string cName, std::string sched, double p);

    // Getters and setters
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
