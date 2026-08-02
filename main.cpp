#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <stdexcept>
#include <string>
#include "Department.h"
#include "Interface.h"
#include "AdminInterface.h"
#include "StudentInterface.h"

// Required Global Variables
Department* StoreDepartments = nullptr;
int TotalDepartments = 0;
const char* csvFile = "data.csv";

// CSV Data Loading Utility
void loadCSVData() {
    std::ifstream file(csvFile);
    if (!file.is_open()) return;

    std::string line;

    // stoi and stod throw if the file contains text where a number belongs.
    // Catch that here so a damaged data file cannot abort the program before
    // the menu is ever shown.
    try {
        if (std::getline(file, line) && !line.empty()) {
            TotalDepartments = std::stoi(line);
            if (TotalDepartments > 0) {
                StoreDepartments = new Department[TotalDepartments];
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

                                // Separate Course Number and Name
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
        // Throw away whatever was read so far and start empty rather than
        // running on half-loaded data.
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
                userInterface->run(); // Polymorphic call
                delete userInterface;
                userInterface = nullptr;
            } else if (choice == 2) {
                userInterface = new AdminInterface();
                userInterface->run(); // Polymorphic call
                delete userInterface;
                userInterface = nullptr;
            }
        } else {
            // End of input (Ctrl+D or a piped file running out). Retrying here would
            // spin forever, because clear() resets the flag and the next read hits
            // EOF again immediately. Break out so the cleanup below still runs.
            if (std::cin.eof()) {
                std::cout << "\nInput ended. Exiting." << std::endl;
                break;
            }

            std::cout << "Error: Invalid input. Enter 1, 2, or 3." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    // Cleanup Global Memory
    delete[] StoreDepartments;
    std::cout << "Exiting system. Goodbye!" << std::endl;

    return 0;
}
