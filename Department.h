#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include "Course.h"
#include <cstring>

// One department and its courses. Owns a heap array, so it needs the full
// Rule of Three.
class Department {
private:
    char name[100];      // char array, not std::string
    Course* courses;     // heap array, resized by hand in addCourse
    int totalCourses;

public:
    Department();
    Department(const char* deptName);
    ~Department();

    // The default copy would copy the pointer, then two Departments free the
    // same array. So we write our own.
    Department(const Department& other);
    Department& operator=(const Department& other);

    const char* getName() const;
    int getTotalCourses() const;
    Course* getCourses() const;

    void setName(const char* deptName);
    void addCourse(const Course& course);
};

#endif
