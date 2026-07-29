#ifndef ADMIN_INTERFACE_H
#define ADMIN_INTERFACE_H

#include "Interface.h"

class AdminInterface : public Interface {
public:
    void run() override;

private:
    // Display all departments
    void listDepartments() const;
    // Add new department
    void addDepartment();
    // Add course to exxisting department
    void addCourseToDepartment();
    // Save all data to CSV file
    void saveChangesToCSV();
};

#endif