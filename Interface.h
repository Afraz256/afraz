#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>

class Interface {
public:
    virtual ~Interface() {}
    virtual void run() = 0; // Pure virtual function for polymorphism

protected:
    // Helper validation methods accessible by derived interface classes
    int getValidIntInput(const std::string& prompt, int min, int max);
    std::string getNonEmptyString(const std::string& prompt);
    double getValidPositiveDouble(const std::string& prompt);
    void printError(const std::string& message) const;
};

#endif