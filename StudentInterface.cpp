#include "StudentInterface.h"
#include "Department.h"
#include <iostream>
#include <iomanip>

// Defined in main.cpp, same ones the admin side uses.
extern Department* StoreDepartments;
extern int TotalDepartments;

void StudentInterface::run() {
    int choice = 0;
    while (choice != 3) {
        std::cout << "\n=== Student Main Menu ===" << std::endl;
        std::cout << "Show Cart [1]\n";
        std::cout << "Browse Departments [2]\n";
        std::cout << "Exit [3]\n";

        choice = getValidIntInput("Enter your choice [1, 2, 3]: ", 1, 3);
        if (choice == INPUT_ABORTED) return;

        switch (choice) {
            case 1: showCartMenu(); break;
            case 2: browseDepartments(); break;
            case 3: break;
        }
    }
}

void StudentInterface::showCartMenu() {
    int choice = 0;
    while (choice != 3) {
        std::cout << "\n--- Cart Menu ---" << std::endl;
        std::cout << "List Courses [1]\n";
        std::cout << "Checkout [2]\n";
        std::cout << "Return to Main Menu [3]\n";

        choice = getValidIntInput("Enter your choice [1, 2, 3]: ", 1, 3);
        if (choice == INPUT_ABORTED) return;

        switch (choice) {
            case 1:
                cart.listCourses();
                break;
            case 2:
                // checkout() empties the cart, then back to the main menu.
                cart.checkout();
                return;
            case 3:
                return;
        }
    }
}

void StudentInterface::browseDepartments() {
    int choice = 0;
    // eof() check stops this menu redrawing after the course menu below bailed.
    while (choice != 2 && !std::cin.eof()) {
        if (TotalDepartments == 0) {
            std::cout << "\nNo departments available." << std::endl;
            return;
        }

        std::cout << "\n--- Available Departments ---" << std::endl;
        for (int i = 0; i < TotalDepartments; ++i) {
            std::cout << i + 1 << ". " << StoreDepartments[i].getName() << std::endl;
        }

        std::cout << "\nOptions:\n1. List Courses of a Department\n2. Go Back to Main Menu\n";
        choice = getValidIntInput("Enter your choice [1, 2]: ", 1, 2);
        if (choice == INPUT_ABORTED) return;

        if (choice == 1) {
            int deptNum = getValidIntInput("Enter department number [0 to go back]: ", 0, TotalDepartments);
            if (deptNum == INPUT_ABORTED) return;
            if (deptNum != 0) {
                listCoursesOfDepartment(deptNum - 1);
            }
        }
    }
}

// deptIndex is 0 based. Menus show 1, 2, 3, so callers subtract 1.
void StudentInterface::listCoursesOfDepartment(int deptIndex) {
    // Reference, to avoid copying the whole Department each time.
    Department& dept = StoreDepartments[deptIndex];
    int choice = 0;

    while (choice != 2) {
        std::cout << "\n--- Courses in " << dept.getName() << " ---" << std::endl;
        if (dept.getTotalCourses() == 0) {
            std::cout << "No courses available in this department." << std::endl;
            return;
        }

        for (int i = 0; i < dept.getTotalCourses(); ++i) {
            Course c = dept.getCourses()[i];
            std::cout << i + 1 << ". " << c.getCourseNumber() << " - " << c.getCourseName()
                      << " | Sched: " << c.getSchedule() << " | Price: $"
                      << std::fixed << std::setprecision(2) << c.getPrice() << std::endl;
        }

        std::cout << "\nOptions:\n1. Add to Cart a Course\n2. Go Back to Browse Departments Menu\n";
        choice = getValidIntInput("Enter your choice [1, 2]: ", 1, 2);
        if (choice == INPUT_ABORTED) return;

        if (choice == 1) {
            int courseNum = getValidIntInput("Enter course number to buy [0 to go back]: ", 0, dept.getTotalCourses());
            if (courseNum == INPUT_ABORTED) return;
            if (courseNum != 0) {
                cart.addCourse(dept.getCourses()[courseNum - 1]);
                std::cout << "Course added to cart." << std::endl;
            }
        }
    }
}
