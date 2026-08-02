#ifndef CART_H
#define CART_H

#include "Course.h"

// What the student picked but hasn't paid for. Same heap array problem as
// Department.
class Cart {
private:
    Course* courses;
    int count;
    double totalCost;    // before tax

    // Static so it belongs to the class, not every Cart. Was a plain const
    // member, which silently deleted the assignment operator below.
    static constexpr double TAX_RATE = 0.13;

public:
    Cart();
    ~Cart();

    // Bare pointer, so the defaults would be shallow. Same as Department.
    Cart(const Cart& other);
    Cart& operator=(const Cart& other);

    void addCourse(const Course& course);
    void listCourses() const;
    void checkout();
    bool isEmpty() const;
    void clear();

    double getSubtotal() const;
    double getTotalWithTax() const;
};

#endif
