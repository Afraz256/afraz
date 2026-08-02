#ifndef STUDENT_INTERFACE_H
#define STUDENT_INTERFACE_H

#include "Interface.h"
#include "Cart.h"

class StudentInterface : public Interface {
private:
    Cart cart;

public:
    void run() override;

private:
    void showCartMenu();
    void browseDepartments();
    void listCoursesOfDepartment(int deptIndex);
};

#endif
