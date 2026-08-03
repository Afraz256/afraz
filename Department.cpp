#include "Department.h"
#include <iostream>
#include <cstring>
#include <cstddef>

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

// Frees the courses array. The Course objects tidy themselves up.
Department::~Department() {
    delete[] courses;
}

// Deep copy. Our own array, nothing shared after this.
Department::Department(const Department& other) {
    setName(other.name);
    totalCourses = other.totalCourses;

    if (totalCourses > 0) {
        courses = new Course[static_cast<std::size_t>(totalCourses)];
        for (int i = 0; i < totalCourses; ++i) {
            courses[i] = other.courses[i];
        }
    } else {
        courses = nullptr;
    }
}

Department& Department::operator=(const Department& other) {
    // Without this, d = d frees d's array then reads from it.
    if (this != &other) {
        delete[] courses;

        setName(other.name);
        totalCourses = other.totalCourses;

        if (totalCourses > 0) {
            courses = new Course[static_cast<std::size_t>(totalCourses)];
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
    // strncpy won't null terminate if it fills the buffer, so we do it.
    strncpy(name, deptName, sizeof(name) - 1);
    name[sizeof(name) - 1] = '\0';
}

/* Arrays can't grow, so "adding" means building a bigger one and copying over.
   Admin adds in any order, so this runs with any number already present. */
void Department::addCourse(const Course& course) {
    /* new[] takes an unsigned size and totalCourses never goes negative, so
       the cast loses nothing. */
    Course* temp = new Course[static_cast<std::size_t>(totalCourses + 1)];
    for (int i = 0; i < totalCourses; ++i) {
        temp[i] = courses[i];
    }
    temp[totalCourses] = course;
    delete[] courses;   // free the old block before repointing, or it leaks
    courses = temp;
    totalCourses++;
}
