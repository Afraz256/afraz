#ifndef STUDENT_INTERFACE_H
#define STUDENT_INTERFACE_H

#include "Interface.h"
#include "Cart.h"

// Student side. Browse departments, add to cart, check out.
class StudentInterface : public Interface {
private:
    // Owned here, so a new StudentInterface starts with an empty cart.
    Cart cart;

public:
    void run() override;

private:
    void showCartMenu();
    void browseDepartments();
    void listCoursesOfDepartment(int deptIndex);
};

#endif
