#include "Interface.h"
#include <iostream>
#include <limits>   // was missing, fixed by L3I
#include <cstddef>

void Interface::printError(const std::string& message) const {
    std::cout << "Error: " << message << std::endl;
}

std::string Interface::trim(const std::string& text) const {
    std::size_t first = text.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) {
        return "";   // nothing but whitespace
    }
    std::size_t last = text.find_last_not_of(" \t\n\r");
    return text.substr(first, last - first + 1);
}

int Interface::getValidIntInput(const std::string& prompt, int min, int max) {
    int choice;
    while (true) {
        std::cout << prompt;
        if (std::cin >> choice && choice >= min && choice <= max) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
        /* This returned max before, which only looked right because max was the
           Exit option. On "[0 to go back]" it picked the last department.
           fixed by L3I */
        if (std::cin.eof()) {
            return INPUT_ABORTED;
        }
        printError("Invalid choice. Please try again.");

        // clear() unjams the stream, ignore() drops what jammed it. Both needed.
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string Interface::getNonEmptyString(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);

        /* Trim before checking. Checking first let "   " through as a name, and
           the caller's trim then turned it into an empty one. fixed by L3I */
        std::string trimmed = trim(input);
        if (!trimmed.empty()) {
            return trimmed;
        }
        /* getline keeps failing at EOF with input left empty, so this would
           spin forever. Empty string is the abort signal. fixed by L3I */
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
        // Same trick, and -1.0 is safe since a real price is always positive.
        if (std::cin.eof()) {
            return -1.0;
        }
        printError("Invalid price. Must be a positive number.");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
