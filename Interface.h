#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>

class Interface {
public:
    virtual ~Interface() {}
    virtual void run() = 0; // Pure virtual function for polymorphism

protected:
    // What getValidIntInput returns when the input stream ends instead of
    // giving us a real choice. -1 is safe because every menu here has a min
    // of 0 or 1, so it can never collide with a valid answer.
    static const int INPUT_ABORTED = -1;

    // Helper validation methods accessible by derived interface classes
    int getValidIntInput(const std::string& prompt, int min, int max);
    std::string getNonEmptyString(const std::string& prompt);
    double getValidPositiveDouble(const std::string& prompt);
    void printError(const std::string& message) const;
};

#endif
