#include <iostream>
#include <limits>
#include "Department.h"
#include "Interface.h"
#include "AdminInterface.h"
#include "StudentInterface.h"
#include "CSVUtils.h"

/* The three globals the project asks for. Every other .cpp reaches them with
   extern, so there is one copy rather than one per file. */
Department* StoreDepartments = nullptr;
int TotalDepartments = 0;
const char* csvFile = "data.csv";

int main() {
    // Fills StoreDepartments. A missing file is not an error, CSVUtils makes one.
    loadFromCSV(csvFile);

    /* An Interface* pointing at a derived object is where the polymorphism
       happens. Which run() executes is decided at runtime, not compile time. */
    Interface* userInterface = nullptr;
    int choice = 0;

    while (choice != 3) {
        std::cout << "=== Course Management System ===" << std::endl;
        std::cout << "1. Student" << std::endl;
        std::cout << "2. Admin" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Enter your choice [1, 2, 3]: ";

        if (std::cin >> choice && (choice >= 1 && choice <= 3)) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (choice == 1) {
                userInterface = new StudentInterface();
                userInterface->run();  // calls StudentInterface::run
                delete userInterface;  // virtual destructor, so the Cart goes too
                userInterface = nullptr;
            } else if (choice == 2) {
                userInterface = new AdminInterface();
                userInterface->run();  // same line, calls AdminInterface::run
                delete userInterface;
                userInterface = nullptr;
            }
        } else {
            /* Input ran out. clear() resets the flag but the next read hits EOF
               again straight away, so retrying here spins forever. fixed by L3I */
            if (std::cin.eof()) {
                std::cout << "\nInput ended. Exiting." << std::endl;
                break;
            }

            std::cout << "Error: Invalid input. Enter 1, 2, or 3." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    // delete[] runs each Department destructor, which frees its own courses.
    delete[] StoreDepartments;
    std::cout << "Exiting system. Goodbye!" << std::endl;

    return 0;
}
