#include "Department.h"
#include <iostream>
#include <cstring>

Department::Department() {
    name[0] = '\0';
    courses = nullptr;
    totalCourses = 0;
}

Department::Department(const char* deptName) {
    setName(deptName);
    courses = nullptr;
    totalCourses = 0;
}

Department::~Department() {
    delete[] courses;
}

// Copy Constructor
Department::Department(const Department& other) {
    setName(other.name);
    totalCourses = other.totalCourses;

    if (totalCourses > 0) {
        courses = new Course[totalCourses];
        for (int i = 0; i < totalCourses; ++i) {
            courses[i] = other.courses[i];
        }
    } else {
        courses = nullptr;
    }
}

// Assignment Operator
Department& Department::operator=(const Department& other) {
    if (this != &other) {
        delete[] courses;

        setName(other.name);
        totalCourses = other.totalCourses;

        if (totalCourses > 0) {
            courses = new Course[totalCourses];
            for (int i = 0; i < totalCourses; ++i) {
                courses[i] = other.courses[i];
            }
        } else {
            courses = nullptr;
        }
    }
    return *this;
}

const char* Department::getName() const { return name; }
int Department::getTotalCourses() const { return totalCourses; }
Course* Department::getCourses() const { return courses; }

void Department::setName(const char* deptName) {
    strncpy(name, deptName, sizeof(name) - 1);
    name[sizeof(name) - 1] = '\0';
}

void Department::addCourse(const Course& course) {
    Course* temp = new Course[totalCourses + 1];
    for (int i = 0; i < totalCourses; ++i) {
        temp[i] = courses[i];
    }
    temp[totalCourses] = course;
    delete[] courses;
    courses = temp;
    totalCourses++;
}
