#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>

// Base class for both interfaces. The menu loop and input checking are the
// same for Admin and Student, so they live here.
class Interface {
public:
    // Virtual because main deletes through an Interface*. Without it only this
    // destructor runs and StudentInterface's Cart leaks.
    virtual ~Interface() {}

    // Pure virtual, so Interface is abstract. main calls this through a base
    // pointer and the right one is picked at runtime. That's the polymorphism.
    virtual void run() = 0;

protected:
    // Returned when input runs out. -1 is safe, menus all start at 0 or 1.
    static const int INPUT_ABORTED = -1;

    // Protected so only the derived interfaces can use them.
    int getValidIntInput(const std::string& prompt, int min, int max);
    std::string getNonEmptyString(const std::string& prompt);
    double getValidPositiveDouble(const std::string& prompt);
    void printError(const std::string& message) const;
};

#endif
