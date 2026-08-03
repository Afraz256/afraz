#include "AdminInterface.h"
#include "Department.h"
#include "CSVUtils.h"
#include <iostream>
#include <cstring>  // strcmp was coming in indirectly, fixed by L3I
#include <cstddef>

// Defined in main.cpp. extern points us at those, no new copies.
extern Department* StoreDepartments;
extern int TotalDepartments;
extern const char* csvFile;

// Menu loop. Print the options, read a choice, dispatch, go round again.
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
        if (choice == INPUT_ABORTED) return;

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
    /* getNonEmptyString trims, so " Math " and "Math" arrive identical and
       can't become two departments. */
    std::string name = getNonEmptyString("Enter department name: ");
    if (name.empty()) return; // input aborted (EOF)

    // strcmp not ==, since getName() returns char* and == compares pointers.
    for (int i = 0; i < TotalDepartments; ++i) {
        if (strcmp(StoreDepartments[i].getName(), name.c_str()) == 0) {
            std::cout << "Error: Department '" << name << "' already exists." << std::endl;
            return;
        }
    }

    /* Grow by one again, this time on the global array. The copy on the line
       below is why Department needs an assignment operator. */
    Department* temp = new Department[static_cast<std::size_t>(TotalDepartments + 1)];
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
    if (deptChoice == INPUT_ABORTED || deptChoice == 0) return;

    // Reference, not a copy. Without & the course gets added to a temporary.
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

// CSVUtils owns the file format. This just triggers the write.
void AdminInterface::saveChangesToCSV() {
    saveToCSV(csvFile);
}
