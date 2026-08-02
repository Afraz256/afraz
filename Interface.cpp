#include "Interface.h"
#include <iostream>

void Interface::printError(const std::string& message) const {
    std::cout << "Error: " << message << std::endl;
}

int Interface::getValidIntInput(const std::string& prompt, int min, int max) {
    int choice;
    while (true) {
        std::cout << prompt;
        if (std::cin >> choice && choice >= min && choice <= max) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
        if (std::cin.eof()) { return max; } // bail out on EOF
        printError("Invalid choice. Please try again.");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string Interface::getNonEmptyString(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        if (!input.empty()) {
            return input;
        }
        printError("Input cannot be empty.");
    }
}

double Interface::getValidPositiveDouble(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value > 0) {
            std::cin.ignore(100, '\n');
            return value;
        }
        printError("Invalid price. Must be a positive number.");
        std::cin.clear();
        std::cin.ignore(100, '\n');
    }
}
