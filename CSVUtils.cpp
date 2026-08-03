#include "CSVUtils.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cstddef>

// Defined in main.cpp, same ones the interfaces use.
extern Department* StoreDepartments;
extern int TotalDepartments;

// Fields are written with ", " between them, so everything after the first
// arrives with a leading space. Strip it or the spaces pile up on every save.
static std::string trim(const std::string& text) {
    std::size_t first = text.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) {
        return "";
    }
    std::size_t last = text.find_last_not_of(" \t\n\r");
    return text.substr(first, last - first + 1);
}

// A data file holding a single 0, which is exactly what saveToCSV writes with
// no departments. Creating it here keeps every file operation in this module.
static bool createEmptyCSV(const char* filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    file << 0 << "\n";
    file.close();
    return true;
}

bool loadFromCSV(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        // Nothing to read, so make one. The next run loads it cleanly.
        std::cout << "CSV file not found. Creating a new one.\n";
        if (!createEmptyCSV(filename)) {
            std::cout << "Could not create " << filename << ". Starting with empty data.\n";
        }
        return false;
    }

    // A failed read or a negative count both mean the file is unusable. A
    // negative would become a huge unsigned size in new[] below and throw.
    if (!(file >> TotalDepartments) || TotalDepartments < 0) {
        std::cout << "CSV file is unreadable. Starting with empty data.\n";
        TotalDepartments = 0;
        return false;
    }
    file.ignore(); // ignore newline

    delete[] StoreDepartments;
    StoreDepartments = new Department[static_cast<std::size_t>(TotalDepartments)];

    std::string line;
    for (int i = 0; i < TotalDepartments; ++i) {
        if (!std::getline(file, line)) {
            // File ended early. Keep what loaded rather than showing blanks.
            TotalDepartments = i;
            break;
        }

        std::stringstream deptStream(line);
        std::string deptName;
        int totalCourses = 0;

        std::getline(deptStream, deptName, ',');
        deptStream >> totalCourses;

        StoreDepartments[i].setName(trim(deptName).c_str());

        if (totalCourses < 0) {
            totalCourses = 0;
        }

        for (int j = 0; j < totalCourses; ++j) {
            if (!std::getline(file, line)) {
                break;
            }

            std::stringstream courseStream(line);
            std::string courseNumber, courseName, schedule;
            double price = 0.0;

            std::getline(courseStream, courseNumber, ',');
            std::getline(courseStream, courseName, ',');
            std::getline(courseStream, schedule, ',');
            courseStream >> price;

            // Every field gets trimmed. Miss the schedule and " M/W" fails the
            // M/W comparison in AdminInterface::addCourseToDepartment.
            StoreDepartments[i].addCourse(Course(trim(courseNumber),
                                                trim(courseName),
                                                trim(schedule),
                                                price));
        }
    }

    file.close();
    std::cout << "Data loaded from CSV successfully.\n";
    return true;
}

bool saveToCSV(const char* filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Failed to open CSV file for writing.\n";
        return false;
    }

    // Default precision is 6 significant digits, so 12345.67 would go out as
    // 12345.7 and lose a cent every time the file is written.
    file << std::fixed << std::setprecision(2);

    file << TotalDepartments << "\n";
    for (int i = 0; i < TotalDepartments; ++i) {
        Department& dept = StoreDepartments[i];
        file << dept.getName() << ", " << dept.getTotalCourses() << "\n";

        for (int j = 0; j < dept.getTotalCourses(); ++j) {
            const Course& c = dept.getCourses()[j];
            file << c.getCourseNumber() << ", " << c.getCourseName() << ", "
                 << c.getSchedule() << ", " << c.getPrice() << "\n";
        }
    }

    file.close();
    // Wording comes from the project spec, so it differs from the supplied file.
    std::cout << "Changes saved successfully.\n";
    return true;
}
