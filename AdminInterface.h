#ifndef ADMIN_INTERFACE_H
#define ADMIN_INTERFACE_H

#include "Interface.h"

// Admin side. Adds departments and courses, saves to CSV.
class AdminInterface : public Interface {
public:
    // override so the compiler errors if this stops matching Interface::run.
    void run() override;

private:
    void listDepartments() const;
    void addDepartment();
    void addCourseToDepartment();
    void saveChangesToCSV();
};

#endif
