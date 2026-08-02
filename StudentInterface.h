#ifndef STUDENT_INTERFACE_H
#define STUDENT_INTERFACE_H

#include "Interface.h"
#include "Cart.h"

// Student side. Browse departments, add to cart, check out.
class StudentInterface : public Interface {
private:
    // Owned by this object, so a fresh StudentInterface means an empty cart.
    Cart cart;

public:
    void run() override;

private:
    void showCartMenu();
    void browseDepartments();
    void listCoursesOfDepartment(int deptIndex);
};

#endif
