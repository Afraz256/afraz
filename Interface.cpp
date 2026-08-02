#include "Interface.h"
#include <iostream>
#include <limits>

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
        // Used to return max, which only looked right because max was Exit.
        // On the "[0 to go back]" prompts it picked the last department.
        if (std::cin.eof()) {
            return INPUT_ABORTED;
        }
        printError("Invalid choice. Please try again.");

        // clear() unjams the stream, ignore() dumps what jammed it. Need both.
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
        // getline keeps failing at EOF and input stays empty, so this would
        // spin forever. Empty string is the abort signal.
        if (std::cin.eof()) {
            return "";
        }
        printError("Input cannot be empty.");
    }
}

double Interface::getValidPositiveDouble(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value > 0) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        // Same trick. -1.0 works since a real price is always positive.
        if (std::cin.eof()) {
            return -1.0;
        }
        printError("Invalid price. Must be a positive number.");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
