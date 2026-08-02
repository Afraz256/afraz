#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <stdexcept>
#include <string>
#include <cstddef>
#include "Department.h"
#include "Interface.h"
#include "AdminInterface.h"
#include "StudentInterface.h"

// Defined here, reached from the interface files with extern.
Department* StoreDepartments = nullptr;
int TotalDepartments = 0;
const char* csvFile = "data.csv";

// File layout: department count, then per department a "name, count" line
// followed by that many "number name, schedule, price" lines.
void loadCSVData() {
    std::ifstream file(csvFile);
    if (!file.is_open()) return;

    std::string line;

    // stoi and stod throw on text where a number should be. Without this a
    // damaged file kills the program before the menu even shows. fixed by L3I
    try {
        if (std::getline(file, line) && !line.empty()) {
            TotalDepartments = std::stoi(line);
            if (TotalDepartments > 0) {
                StoreDepartments = new Department[static_cast<std::size_t>(TotalDepartments)];
                for (int i = 0; i < TotalDepartments; ++i) {
                    if (std::getline(file, line)) {
                        std::stringstream ss(line);
                        std::string deptName, countStr;
                        std::getline(ss, deptName, ',');
                        std::getline(ss, countStr, ',');

                        StoreDepartments[i].setName(deptName.c_str());
                        int courseCount = std::stoi(countStr);

                        for (int j = 0; j < courseCount; ++j) {
                            if (std::getline(file, line)) {
                                std::stringstream cSS(line);
                                std::string fullName, schedule, priceStr;

                                std::getline(cSS, fullName, ',');
                                std::getline(cSS, schedule, ',');
                                std::getline(cSS, priceStr, ',');

                                // Split "PRG210 Programming" at the first space.
                                std::stringstream nameSS(fullName);
                                std::string cNum, cName;
                                nameSS >> cNum;
                                std::getline(nameSS, cName);
                                if (!cName.empty() && cName[0] == ' ') {
                                    cName = cName.substr(1);
                                }

                                // Trim leading space for schedule
                                if (!schedule.empty() && schedule[0] == ' ') {
                                    schedule = schedule.substr(1);
                                }

                                double price = std::stod(priceStr);
                                Course c(cNum, cName, schedule, price);
                                StoreDepartments[i].addCourse(c);
                            }
                        }
                    }
                }
            }
        }
    } catch (const std::exception& e) {
        // Drop whatever loaded rather than running on half read data.
        std::cout << "Warning: could not read " << csvFile << " (" << e.what()
                  << "). Starting with no departments." << std::endl;
        delete[] StoreDepartments;
        StoreDepartments = nullptr;
        TotalDepartments = 0;
    }

    file.close();
}

int main() {
    loadCSVData();

    // Base class pointer. It holds whichever derived interface the user picks,
    // which is what makes the run() calls below polymorphic.
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
                userInterface->run(); // picks StudentInterface::run at runtime
                delete userInterface; // virtual destructor, so the Cart goes too
                userInterface = nullptr;
            } else if (choice == 2) {
                userInterface = new AdminInterface();
                userInterface->run(); // same call, different function
                delete userInterface;
                userInterface = nullptr;
            }
        } else {
            // Input ran out. Retrying would spin forever since clear() resets
            // the flag and the next read hits EOF again. fixed by L3I
            if (std::cin.eof()) {
                std::cout << "\nInput ended. Exiting." << std::endl;
                break;
            }

            std::cout << "Error: Invalid input. Enter 1, 2, or 3." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    // delete[] runs every Department destructor, and each frees its own courses.
    delete[] StoreDepartments;
    std::cout << "Exiting system. Goodbye!" << std::endl;

    return 0;
}
