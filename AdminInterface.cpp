#include "AdminInterface.h"
#include "Department.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

extern Department* StoreDepartments;
extern int TotalDepartments;
extern const char* csvFile;

void AdminInterface::run() {
    int choice = 0;
    while (choice != 5) {
        std::cout << "\n=== Admin Main Menu ===" << std::endl;
        std::cout << "List Departments [1]\n";
        std::cout << "Add Department [2]\n";
        std::cout << "Add Course to Department [3]\n";
        std::cout << "Save Changes to CSV [4]\n";
        std::cout << "Exit [5]\n";

        choice = getValidIntInput("Enter your choice [1, 2, 3, 4, 5]: ", 1, 5);

        switch (choice) {
            case 1: listDepartments(); break;
            case 2: addDepartment(); break;
            case 3: addCourseToDepartment(); break;
            case 4: saveChangesToCSV(); break;
            case 5: break;
        }
    }
}

void AdminInterface::listDepartments() const {
    if (TotalDepartments == 0) {
        std::cout << "\nNo departments available." << std::endl;
        return;
    }
    std::cout << "\n--- Department List ---" << std::endl;
    for (int i = 0; i < TotalDepartments; ++i) {
        std::cout << i + 1 << ". " << StoreDepartments[i].getName() << std::endl;
    }
}

void AdminInterface::addDepartment() {
    std::string name = getNonEmptyString("Enter department name: ");
    if (name.empty()) return; // input aborted (EOF)

    // Trim whitespace from name
    name.erase(0, name.find_first_not_of(" \t\n\r"));
    name.erase(name.find_last_not_of(" \t\n\r") + 1);

    // Check if department already exists
    for (int i = 0; i < TotalDepartments; ++i) {
        if (strcmp(StoreDepartments[i].getName(), name.c_str()) == 0) {
            std::cout << "Error: Department '" << name << "' already exists." << std::endl;
            return;
        }
    }

    // Create new array with one extra slot
    Department* temp = new Department[TotalDepartments + 1];
    for (int i = 0; i < TotalDepartments; ++i) {
        temp[i] = StoreDepartments[i];
    }
    temp[TotalDepartments].setName(name.c_str());

    delete[] StoreDepartments;
    StoreDepartments = temp;
    TotalDepartments++;

    std::cout << "Department '" << name << "' added successfully." << std::endl;
}

void AdminInterface::addCourseToDepartment() {
    if (TotalDepartments == 0) {
        std::cout << "\nNo departments available to add courses." << std::endl;
        return;
    }

    listDepartments();
    int deptChoice = getValidIntInput("Enter department number [0 to go back]: ", 0, TotalDepartments);
    if (deptChoice == 0) return;

    Department& selectedDept = StoreDepartments[deptChoice - 1];

    std::cout << "\nExisting courses in " << selectedDept.getName() << ":" << std::endl;
    for (int i = 0; i < selectedDept.getTotalCourses(); ++i) {
        Course c = selectedDept.getCourses()[i];
        std::cout << i + 1 << ". " << c.getCourseNumber() << " - " << c.getCourseName() << std::endl;
    }

    std::string cNum = getNonEmptyString("Enter course number: ");
    if (cNum.empty()) return; // input aborted (EOF)

    std::string cName = getNonEmptyString("Enter course name: ");
    if (cName.empty()) return; // input aborted (EOF)

    std::string schedule;
    while (true) {
        schedule = getNonEmptyString("Enter course schedule (M/W, T/R, W/F): ");
        if (schedule.empty()) return; // input aborted (EOF)
        if (schedule == "M/W" || schedule == "T/R" || schedule == "W/F") {
            break;
        }
        printError("Only accept 'M/W', 'T/R', 'W/F' for schedule.");
    }

    double price = getValidPositiveDouble("Enter course price: ");
    if (price < 0) return; // input aborted (EOF)

    Course newCourse(cNum, cName, schedule, price);
    selectedDept.addCourse(newCourse);

    std::cout << "Course added successfully." << std::endl;
}

void AdminInterface::saveChangesToCSV() {
    std::ofstream file(csvFile);
    if (!file.is_open()) {
        printError("Failed to open CSV file for writing.");
        return;
    }

    // Default stream precision is 6 significant digits, so a price like
    // 12345.67 gets written as 12345.7 and loses a cent on every reload.
    // Set it once here. Integers are unaffected by this.
    file << std::fixed << std::setprecision(2);

    file << TotalDepartments << "\n";
    for (int i = 0; i < TotalDepartments; ++i) {
        file << StoreDepartments[i].getName() << ", " << StoreDepartments[i].getTotalCourses() << "\n";
        for (int j = 0; j < StoreDepartments[i].getTotalCourses(); ++j) {
            Course c = StoreDepartments[i].getCourses()[j];
            file << c.getCourseNumber() << " " << c.getCourseName() << ", " << c.getSchedule() << ", " << c.getPrice() << "\n";
        }
    }

    file.close();
    std::cout << "Changes saved successfully." << std::endl;
}
