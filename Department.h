#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include "Course.h"
#include <cstring>

// Represents the department (e.g. "Computer Science", "Mathematics").
class Department {
private:
    char name[100];
    Course* courses;
    int totalCourses;

public:
    Department();
    Department(const char* deptName);
    ~Department();

    // Copy Constructor & Assignment Operator for Deep Copying
    Department(const Department& other);
    Department& operator=(const Department& other);

    // Getters
    const char* getName() const;
    int getTotalCourses() const;
    Course* getCourses() const;

    // Setters & Actions
    void setName(const char* deptName);
    void addCourse(const Course& course);
};

#endif
